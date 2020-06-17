#include <cstdlib>

#include "NetManager.h"
#include "TcpConn.h"
#include "../util/DebugPrint.h"
#include "../message/Codec.h"
#include "../log/Logger.h"

namespace rdm {

TcpConn::TcpConn(boost::asio::io_service& io_service)
        : socket_(io_service) {

}

TcpConn::~TcpConn() {
    socket_.close();
}

TcpConn::sptr TcpConn::create(boost::asio::io_context& io_service) {
    return static_cast<sptr>(new TcpConn(io_service));
}

void TcpConn::read() {
    socket_.async_read_some(
            boost::asio::buffer(data_, max_length),
            boost::bind(&TcpConn::handleRead,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void TcpConn::write(const std::string& str) {
    socket_.async_write_some(
            boost::asio::buffer(str.c_str(), str.length()),
            boost::bind(&TcpConn::handleWrite, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

tcp::socket& TcpConn::getSocket() {
    return socket_;
}

void TcpConn::onConnect() {
    remote_addr = socket_.remote_endpoint().address().to_string();
    remote_port = socket_.remote_endpoint().port();
    LOG_ERROR("{},{}", remote_addr, remote_port);
    read();
}

void TcpConn::handleWrite(const boost::system::error_code& ec,
                          std::size_t bytes_transferred) {
    if (ec) {
        LOG_ERROR("write size {} error, {}", bytes_transferred, ec.message());
    } else {
        // LOG_DEBUG("send size: {}", bytes_transferred);
    }
}

void TcpConn::handleRead(const boost::system::error_code& ec,
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
        write(std::string(data_, bytes_transferred));
        if (mode_ & kDebug) {
            LOG_DEBUG("send data {}: {}, ",
                      bytes_transferred,
                      bytes_transferred < 20 ? DebugPrint::StringToDecSet(std::string(data_, bytes_transferred))
                                             : "data is long...");
        }
        read();
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

    read();
}

void TcpConn::setConnId(uint32_t connId) {
    conn_id_ = connId;
}

uint32_t TcpConn::getConnId() const {
    return conn_id_;
}

std::string TcpConn::localAddr() const {
    return socket_.local_endpoint().address().to_string() + std::to_string(socket_.local_endpoint().port());
}

std::string TcpConn::remoteAddr() const {
    return socket_.remote_endpoint().address().to_string() + std::to_string(socket_.remote_endpoint().port());
}

void TcpConn::close() {
    socket_.close();
}

void TcpConn::closeRead() {
    boost::system::error_code ec;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_receive, ec);
    if (ec) {
        LOG_ERROR("close read error, {}", ec.message());
    }
}

void TcpConn::closeWrite() {
    boost::system::error_code ec;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
    if (ec) {
        LOG_ERROR("close write error, {}", ec.message());
    }
}

int32_t TcpConn::fd() {
    return socket_.native_handle();
}

}