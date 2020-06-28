#include <iostream>

#include <boost/bind.hpp>

#include "../log/Logger.h"
#include "NetClient.h"
#include"../thread/ThreadUtil.h"
#include "../message/Codec.h"

namespace rdm {

NetClient::NetClient(boost::asio::io_service* io_context)
        : io_context_(io_context),
          socket_(nullptr),
          is_connected_(false),
          reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    socket_ = new tcp::socket(*io_context);

    reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    message_subject_ = std::make_shared<MessageSubject>();
}

NetClient::NetClient(boost::asio::io_service* io_context,
                     const std::string& ip,
                     const std::string& port)
        : io_context_(io_context),
          socket_(nullptr),
          is_connected_(false),
          reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    socket_ = new tcp::socket(*io_context);

    reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    message_subject_ = std::make_shared<MessageSubject>();

    tcp::resolver resolver(*io_context_);
    endpoints_ = resolver.resolve(ip, port);
    start();
}

NetClient::NetClient(boost::asio::io_service* io_context,
                     const boost::asio::ip::tcp::resolver::results_type& endpoints)
        : io_context_(io_context),
          socket_(nullptr),
          is_connected_(false),
          reconnect_timer_(*io_context, boost::posix_time::seconds(3)) {
    socket_ = new tcp::socket(*io_context);

    reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));

    message_subject_ = std::make_shared<MessageSubject>();

    endpoints_ = endpoints;

    start();
}

void NetClient::write(const std::string& msg) {
    boost::asio::post(*io_context_,
                      [this, msg]() {
                          bool write_in_progress = !write_message_.empty();
                          write_message_.push_back(msg);
                          if (!write_in_progress) {
                              doWrite();
                          }
                      });
}

void NetClient::close() {
    boost::asio::post(*io_context_,
                      [this]() {
                          socket_->close();
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
        socket_->close();
        if (socket_ != nullptr) {
            delete socket_;
            socket_ = nullptr;
        }
        socket_ = new tcp::socket(*io_context_);
        start();
    }

    // 每 3 秒检查一次连接状态
    reconnect_timer_.expires_at(reconnect_timer_.expires_at() + boost::posix_time::seconds(3));
    reconnect_timer_.async_wait(boost::bind(&NetClient::restart, this));
}

void NetClient::registMessage(const std::string& message_name, IObserver* observer) {
    message_subject_->registObserver(message_name, observer);
}

std::shared_ptr<MessageSubject> NetClient::getMessageSubject() {
    return message_subject_;
}

bool NetClient::isConnected() const {
    return is_connected_;
}

void NetClient::doConnect(const std::string& ip, const std::string& port) {
    tcp::resolver resolver(*io_context_);
    doConnect(resolver.resolve(ip, port));
}

void NetClient::doConnect(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    if (socket_ == nullptr) {
        LOG_ERROR("socket is null");
        return;
    }

    for (auto& item : endpoints) {
        LOG_INFO("try connect to {}:{}",
                 item.endpoint().address().to_string(),
                 item.endpoint().port());
    }

    // 开始异步连接
    boost::asio::async_connect(*socket_,
                               endpoints,
                               [this](boost::system::error_code ec,
                                      const boost::asio::ip::tcp::endpoint&) {
                                   if (stopped_) {
                                       LOG_ERROR("this socket is stopped, {}", ec.message());
                                       return;
                                   } else if (!socket_->is_open()) {
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
    socket_->async_read_some(boost::asio::buffer(read_message_, kMessageLengthMax),
                             boost::bind(&NetClient::handleRead,
                                         this,
                                         boost::placeholders::_1,
                                         boost::placeholders::_2));
}

void NetClient::doWrite() {
    boost::asio::async_write(*socket_,
                             boost::asio::buffer(write_message_.front(),
                                                 write_message_.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (stopped_) {
                                     LOG_ERROR("the net client is stopped");
                                     return;
                                 }

                                 if (!ec) {
                                     write_message_.pop_front();
                                     if (!write_message_.empty()) {
                                         doRead();
                                     }
                                 } else {
                                     LOG_ERROR("{}", ec.message());
                                     is_connected_ = false;
                                 }
                             });
}

void NetClient::handleRead(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (stopped_) {
        LOG_ERROR("the net client is stopped");
        return;
    }

    if (ec) {
        LOG_ERROR("{}", ec.message());
        is_connected_ = false;
        socket_->close();
        return;
    }

    const std::string read_data(read_message_, bytes_transferred);

    read_message_buffer_ += read_data;
    while (true) {
        // 粘包处理
        if (read_message_buffer_.length() >= 4) {
            try {
                uint32_t len = byte4ToUint32(read_message_buffer_);

                if (read_message_buffer_.length() >= len + 4) {
                    std::string read_msg = read_message_buffer_.substr(0, len + 4);
                    read_message_buffer_ = read_message_buffer_.substr(len + 4);

                    NetMsg net_msg;
                    net_msg.bind(&read_msg, socket_);
                    message_subject_->resolveMessage(&net_msg);
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
}

}