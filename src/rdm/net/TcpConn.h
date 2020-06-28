#pragma once

#include <memory>

#include <boost/asio.hpp>

#include "Net.h"

using boost::asio::ip::tcp;

namespace rdm {

/*
 * 封装 boost::asio::ip::tcp::socket_
 */
class TcpConn
        : public std::enable_shared_from_this<TcpConn> {
public:
    using sptr = std::shared_ptr<TcpConn>;

    // 工作模式
    enum WorkMode : uint32_t {
        kDebug = 1u << 1u,         // 打印收发数据
        kEchoMode = 1u << 2u,      // 收到消息，直接返回
        kMessageMode = 1u << 3u,   // 消息分发
    };

    ~TcpConn();

    static sptr create(boost::asio::io_context& io_service);

    tcp::socket& getSocket();

    void onConnect();

    void write(const std::string& str);

    uint32_t getConnId() const;
    void setConnId(uint32_t conn_id);

    Addr localAddr() const;
    Addr remoteAddr() const;
    int32_t fd();
    void close();
    void closeRead();
    void closeWrite();

private:
    explicit TcpConn(boost::asio::io_service& io_service);

    void read();

    void handleWrite(const boost::system::error_code& ec, size_t bytes_transferred);
    void handleRead(const boost::system::error_code& ec, size_t bytes_transferred);

    // boost::asio::streambuf message_;
    // std::string message_;

    enum {
        max_length = 1024
    };
    char data_[max_length]{0};
    tcp::socket socket_;
    bool is_connected_{false};

    uint32_t conn_id_{0};
    uint64_t session_id_{0};

    std::string read_message_buffer_; // 消息缓冲区，如果接受到的消息不完整，先存起来等下个 TCP 包

    uint8_t mode_{kDebug | kMessageMode};

    // todo cwj 临时变量，考虑是否优化
    std::string remote_addr_;
    uint16_t remote_port_{0};
};

}

