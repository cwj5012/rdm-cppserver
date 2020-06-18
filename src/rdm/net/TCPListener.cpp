#include "TCPListener.h"
#include "../log/Logger.h"
#include "NetManager.h"
#include <boost/lexical_cast.hpp>

namespace rdm {

TCPListener::TCPListener(boost::asio::io_service& io_service)
        : io_context_(io_service) {

}

TCPListener::TCPListener(boost::asio::io_service& io_service, const std::string& host, uint16_t port)
        : io_context_(io_service) {
    bind(io_service, host, port);
    accept();
}

TCPListener::~TCPListener() {

}

void TCPListener::bind(boost::asio::io_service& io_service, const std::string& host, uint16_t port) {
    address addr = address::from_string(host);
    endpoint_ = std::make_unique<tcp::endpoint>(addr, port);
    accecptor_ = std::make_unique<tcp::acceptor>(io_service, *endpoint_);
}

TcpConn::sptr TCPListener::getConnection(uint32_t conn_id) {
    auto it = conns_.find(conn_id);
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

TcpConn::sptr TCPListener::getConnection() {
    auto it = conns_.begin();
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<TcpConn::sptr> TCPListener::getConnections() {
    std::vector<TcpConn::sptr> cons;
    for (const auto& it : conns_) {
        cons.push_back(it.second);
    }
    return cons;
}

void TCPListener::accept() {
    TcpConn::sptr new_connection = TcpConn::create(io_context_);
    accecptor_->async_accept(new_connection->getSocket(),
                             boost::bind(&TCPListener::handleAccept,
                                         this,
                                         new_connection,
                                         boost::asio::placeholders::error));
}

void TCPListener::handleAccept(const TcpConn::sptr& new_conn,
                               const boost::system::error_code& ec) {
    if (!ec) {
        new_conn->setConnId(NetManager::inst().getConnUid());
        conns_[new_conn->getConnId()] = new_conn;
        LOG_INFO("a client connected id: {}, {}:{}.",
                 new_conn->getConnId(),
                 new_conn->getSocket().remote_endpoint().address().to_string(),
                 new_conn->getSocket().remote_endpoint().port());
        new_conn->onConnect();
    } else {
        LOG_ERROR("{}", ec.message());
        return;
    }

    accept();
}

int32_t TCPListener::fd() const {
    return accecptor_->native_handle();
}

Addr TCPListener::addr() const {
    Addr addr(accecptor_->local_endpoint().protocol().type(),
              accecptor_->local_endpoint().address().to_string(),
              accecptor_->local_endpoint().port());
    return addr;
}

} // namespace rdm