#include <iostream>

#include <boost/bind.hpp>

#include "../log/Logger.h"
#include "NetClient.h"
#include"../thread/ThreadUtil.h"
#include "../message/Codec.h"

namespace rdm {

NetClient::NetClient(boost::asio::io_service* io_context)
        : mIoContext(io_context),
          mSocket(nullptr),
          is_connected_(false),
          m_reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    mSocket = new tcp::socket(*io_context);

    m_reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    mMessageSubject = std::make_shared<MessageSubject>();
}

NetClient::NetClient(boost::asio::io_service* io_context,
                     const std::string& ip,
                     const std::string& port)
        : mIoContext(io_context),
          mSocket(nullptr),
          is_connected_(false),
          m_reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    mSocket = new tcp::socket(*io_context);

    m_reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    mMessageSubject = std::make_shared<MessageSubject>();

    tcp::resolver resolver(*mIoContext);
    endpoints_ = resolver.resolve(ip, port);
    start();
}

NetClient::NetClient(boost::asio::io_service* io_context,
                     const boost::asio::ip::tcp::resolver::results_type& endpoints)
        : mIoContext(io_context),
          mSocket(nullptr),
          is_connected_(false),
          m_reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    mSocket = new tcp::socket(*io_context);

    m_reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    mMessageSubject = std::make_shared<MessageSubject>();

    endpoints_ = endpoints;

    start();
}

void NetClient::write(const std::string& msg) {
    boost::asio::post(*mIoContext,
                      [this, msg]() {
                          bool write_in_progress = !mWriteMessages.empty();
                          mWriteMessages.push_back(msg);
                          if (!write_in_progress) {
                              doWrite();
                          }
                      });
}

void NetClient::read() {
    doRead();
}

void NetClient::close() {
    boost::asio::post(*mIoContext,
                      [this]() {
                          mSocket->close();
                      });
}

void NetClient::start() {
    doConnect();
}

void NetClient::stop() {
    stopped_ = true;
    is_connected_ = false;
}

void NetClient::restart() {
    if (!isConnected()) {
        mSocket->close();
        if (mSocket != nullptr) {
            delete mSocket;
            mSocket = nullptr;
        }
        mSocket = new tcp::socket(*mIoContext);
        start();
    }

    // 每 3 秒检查一次连接状态
    m_reconnect_timer_.expires_at(m_reconnect_timer_.expires_at() + boost::posix_time::seconds(3));
    m_reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));
}

void NetClient::registMessage(const std::string& message_name, IObserver* observer) {
    mMessageSubject->registObserver(message_name, observer);
}

std::shared_ptr<MessageSubject> NetClient::getMessageSubject() {
    return mMessageSubject;
}

bool NetClient::isConnected() const {
    return is_connected_;
}

void NetClient::doConnect(const std::string& ip, const std::string& port) {
    tcp::resolver resolver(*mIoContext);
    doConnect(resolver.resolve(ip, port));
}

void NetClient::doConnect(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    if (mSocket == nullptr) {
        LOG_ERROR("socket is null");
        return;
    }

    for (auto& item : endpoints) {
        LOG_INFO("try connect to {}:{}",
                 item.endpoint().address().to_string(),
                 item.endpoint().port());
    }

    // 开始异步连接
    boost::asio::async_connect(*mSocket,
                               endpoints,
                               [this](boost::system::error_code ec,
                                      const boost::asio::ip::tcp::endpoint&) {
                                   if (stopped_) {
                                       LOG_ERROR("this socket is stopped, {}", ec.message());
                                       return;
                                   } else if (!mSocket->is_open()) {
                                       LOG_ERROR("{}", ec.message());
                                       return;
                                   } else if (ec) {
                                       LOG_ERROR("{}", ec.message());
                                       close();
                                       return;
                                   }

                                   for (auto& item : this->endpoints_) {
                                       LOG_INFO("connectd to {}:{}",
                                                item.endpoint().address().to_string(),
                                                item.endpoint().port());
                                   }

                                   is_connected_ = true;
                                   doRead();
                               }
    );
}

void NetClient::handleConnect(const boost::system::error_code& ec,
                              tcp::resolver::iterator endpoint_iter) {
    LOG_INFO("handleConnect");
}

void NetClient::doConnect() {
    doConnect(endpoints_);
}

void NetClient::doRead() {
    mSocket->async_read_some(boost::asio::buffer(mReadMessage, 1024),
                             [this](boost::system::error_code ec, std::size_t bytes_transferred) {
                                 if (stopped_) {
                                     LOG_ERROR("the net client is stopped");
                                     return;
                                 }

                                 if (!ec) {
                                     const std::string read_data(mReadMessage, bytes_transferred);

                                     mReadMessageBuffer += read_data;
                                     while (true) {
                                         // 粘包处理
                                         if (mReadMessageBuffer.length() >= 4) {
                                             std::string len_str = mReadMessageBuffer.substr(0, 4);
                                             try {
                                                 uint32_t len = byte4ToUint32(len_str);

                                                 if (mReadMessageBuffer.length() >= len + 4) {
                                                     std::string read_msg = mReadMessageBuffer.substr(0, len + 4);
                                                     mReadMessageBuffer = mReadMessageBuffer.substr(len + 4);

                                                     NetMsg net_msg;
                                                     net_msg.bind(&read_msg, mSocket);
                                                     mMessageSubject->resolveMessage(&net_msg);
                                                 } else {
                                                     // 收到的数据长度不足，等待下一个包
                                                     break;
                                                 }
                                             } catch (std::exception& e) {
                                                 LOG_ERROR("get message length failed, {}", e.what());
                                                 return;
                                             }
                                         } else {
                                             break;
                                         }
                                     }

                                     doRead();
                                 } else {
                                     LOG_ERROR("{}", ec.message());
                                     is_connected_ = false;
                                 }
                             });
}

void NetClient::doWrite() {
    boost::asio::async_write(*mSocket,
                             boost::asio::buffer(mWriteMessages.front(),
                                                 mWriteMessages.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (stopped_) {
                                     LOG_ERROR("the net client is stopped");
                                     return;
                                 }

                                 if (!ec) {
                                     mWriteMessages.pop_front();
                                     if (!mWriteMessages.empty()) {
                                         doRead();
                                     }
                                 } else {
                                     LOG_ERROR("{}", ec.message());
                                     is_connected_ = false;
                                 }
                             });
}
}