/*
 * 封装 boost::asio::ip::tcp::socket_
 */

#pragma once

#include <memory>
#include <functional>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

namespace rdm {

class NetConnection
        : public std::enable_shared_from_this<NetConnection> {
public:
    ~NetConnection();

    typedef std::shared_ptr<NetConnection> ptrConnection;

    static ptrConnection create(boost::asio::io_context& io_service);

    tcp::socket& getSocket();

    void start();

    void setPlayerID(uint64_t id);

    uint64_t getPlayerID();

    void doWrite(const std::string& str);

private:
    explicit NetConnection(boost::asio::io_service& io_service);

    void doRead();

    void doWrite(std::size_t length);


    void handleWrite(const boost::system::error_code& ec, size_t bytes_transferred);

    void handleRead(const boost::system::error_code& ec, size_t bytes_transferred);

    tcp::socket socket_;

    // boost::asio::streambuf message_;
    // std::string message_;

    enum {
        max_length = 1024
    };
    char data_[max_length];

    uint64_t mPlayerID;

    std::string mReadMessageBuffer; // 消息缓冲区，如果接受到的消息不完整，先存起来等下个 TCP 包
};

}

