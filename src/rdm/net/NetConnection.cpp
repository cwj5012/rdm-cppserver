#include <cstdlib>

#include "NetManager.h"
#include "NetConnection.h"
#include "../util/DebugPrint.h"
#include "../message/Codec.h"
#include "../log/Logger.h"

namespace rdm {

NetConnection::NetConnection(boost::asio::io_service& io_service)
        : socket_(io_service) {

}

NetConnection::~NetConnection() {
    socket_.close();
}

NetConnection::sptr NetConnection::create(boost::asio::io_context& io_service) {
    return static_cast<sptr>(new NetConnection(io_service));
}

void NetConnection::doRead() {
    socket_.async_read_some(
            boost::asio::buffer(data_, max_length),
            boost::bind(&NetConnection::handleRead,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void NetConnection::doWrite(std::size_t bytes_transferred) {
    std::string write_data(data_, bytes_transferred);
    socket_.async_write_some(
            boost::asio::buffer(data_, bytes_transferred),
            boost::bind(&NetConnection::handleWrite, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void NetConnection::doWrite(const std::string& str) {
    socket_.async_write_some(
            boost::asio::buffer(str.c_str(), str.length()),
            boost::bind(&NetConnection::handleWrite, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

tcp::socket& NetConnection::getSocket() {
    return socket_;
}

void NetConnection::start() {
    remote_addr = socket_.remote_endpoint().address().to_string();
    remote_port = socket_.remote_endpoint().port();
    doRead();
}

void NetConnection::handleWrite(const boost::system::error_code& ec,
                                std::size_t bytes_transferred) {
    if (ec) {
        LOG_INFO("write error, {}", ec.message());
    } else {
        // LOG_DEBUG("send size: {}", bytes_transferred);
    }
    // doRead();
}

void NetConnection::handleRead(const boost::system::error_code& ec,
                               std::size_t bytes_transferred) {
    if (ec /* && ec != boost::asio::error::eof */) {
        LOG_INFO("client disconnectd, {}:{}, {}",
                 remote_addr,
                 remote_port,
                 ec.message());
        socket_.close();
        return;
    }

    const std::string read_data(data_, bytes_transferred);
    if (mode_ & kDebug) {
        LOG_DEBUG("recv data {}: {}",
                  bytes_transferred,
                  bytes_transferred < 80 ? DebugPrint::StringToDecSet(read_data) : "data is long...");
    }

    if (mode_ & kEchoMode) {
        doWrite(std::string(data_, bytes_transferred));
        if (mode_ & kDebug) {
            LOG_DEBUG("send data {}: {}, ",
                      bytes_transferred,
                      bytes_transferred < 20 ? DebugPrint::StringToDecSet(std::string(data_, bytes_transferred))
                                             : "data is long...");
        }
        doRead();
        return;
    }

    read_message_buffer_ += read_data;
    while (true) {
        // 粘包处理
        if (read_message_buffer_.length() >= 4) {
            try {
                auto len = byte4ToUint32(read_message_buffer_);

                if (mode_ & kDebug) {
                    LOG_DEBUG("recv body size: {}", len);
                }
                if (read_message_buffer_.length() >= len + 4) {
                    // 提取消息
                    std::string read_msg = read_message_buffer_.substr(4, len);

                    // 截断消息
                    read_message_buffer_ = read_message_buffer_.substr(len + 4);

                    if (mode_ & kDebug) {
                        LOG_DEBUG("recv body: {}", DebugPrint::StringToDecSet(read_msg));
                        LOG_DEBUG("buff size: {}", read_message_buffer_.size());
                    }
                    NetMsg net_msg;
                    net_msg.bind(&read_msg, &socket_);
                    NetManager::inst().getMessageSubject()->resolveMessage(&net_msg);
                } else {
                    // 收到的数据长度不足，等待下个包
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

void NetConnection::setConnId(uint32_t connId) {
    conn_id_ = connId;
}

uint32_t NetConnection::getConnId() const {
    return conn_id_;
}

}