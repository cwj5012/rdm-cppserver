﻿#pragma once

#include <memory>
#include <functional>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

namespace rdm {

/*
 * 封装 boost::asio::ip::tcp::socket_
 */
class NetConnection
        : public std::enable_shared_from_this<NetConnection> {
public:
    using sptr = std::shared_ptr<NetConnection>;

    // 工作模式
    enum {
        kDebug = 1 << 1u,         // 打印收发数据
        kEchoMode = 1 << 2u,      // 收到消息，直接返回
        kMessageMode = 1 << 3u,   // 消息分发
    };

    ~NetConnection();

    static sptr create(boost::asio::io_context& io_service);

    tcp::socket& getSocket();

    void start();

    void doWrite(const std::string& str);

    uint32_t getConnId() const;
    void setConnId(uint32_t connId);

private:
    explicit NetConnection(boost::asio::io_service& io_service);

    void doRead();
    void doWrite(std::size_t length);

    void handleWrite(const boost::system::error_code& ec, size_t bytes_transferred);
    void handleRead(const boost::system::error_code& ec, size_t bytes_transferred);

    // boost::asio::streambuf message_;
    // std::string message_;

    enum {
        max_length = 1024
    };
    char data_[max_length]{0};
    uint32_t conn_id_{0};
    tcp::socket socket_;
    std::string mReadMessageBuffer; // 消息缓冲区，如果接受到的消息不完整，先存起来等下个 TCP 包

    std::string remote_addr;
    uint16_t remote_port{0};
    uint8_t mode_{kDebug | kMessageMode};
};

}

