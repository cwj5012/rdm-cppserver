#include <cstdlib>

#include "NetManager.h"
#include "NetConnection.h"
#include "../util/DebugPrint.h"
#include "../message/Codec.h"
#include "../log/Logger.h"

namespace rdm {

NetConnection::NetConnection(boost::asio::io_service& io_service)
        : socket_(io_service),
          mPlayerID(0) {

}

NetConnection::~NetConnection() {

}

NetConnection::ptrConnection NetConnection::create(boost::asio::io_context& io_service) {
    return static_cast<ptrConnection>(new NetConnection(io_service));
}

void NetConnection::doRead() {
    // LOG_INFO("NetConnection: do read");
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
    doRead();
}

void NetConnection::setPlayerID(uint64_t id) {
    mPlayerID = id;
}

uint64_t NetConnection::getPlayerID() {
    return mPlayerID;
}

void NetConnection::handleWrite(const boost::system::error_code& ec,
                                std::size_t bytes_transferred) {
    // LOG_INFO("NetConnection: handle write");
    // doRead();
}

void NetConnection::handleRead(const boost::system::error_code& ec,
                               std::size_t bytes_transferred) {
    if (ec /* && ec != boost::asio::error::eof */) {
        LOG_ERROR("{}", ec.message());
        socket_.close();
        return;
    }

    const std::string read_data(data_, bytes_transferred);

    mReadMessageBuffer += read_data;
    while (true) {
        // 粘包处理
        if (mReadMessageBuffer.length() >= 4) {
            std::string len_str = mReadMessageBuffer.substr(0, 4);
            try {
                int32_t len = int32_t((uint8_t) (len_str[0]) << 24 |
                                      (uint8_t) (len_str[1]) << 16 |
                                      (uint8_t) (len_str[2]) << 8 |
                                      (uint8_t) (len_str[3]));

                if (mReadMessageBuffer.length() >= len + 4) {
                    std::string read_msg = mReadMessageBuffer.substr(0, len + 4);
                    mReadMessageBuffer = mReadMessageBuffer.substr(len + 4);

                    NetMsg net_msg;
                    net_msg.bind(&read_msg, &socket_);
                    NetManager::inst().getMessageSubject()->resolveMessage(&net_msg);
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

//        NetMsg net_msg;
//        net_msg.bind(&read_data, &socket_);
//        NetManager::inst().getMessageSubject()->resolveMessage(&net_msg);

//        std::string messageRequest;
//        {
//            std::stringstream ss;
//            ss << &message_;
//            ss.flush();
//            messageRequest = ss.str();
//        }

    doRead();
    //doWrite(bytes_transferred);
}

}