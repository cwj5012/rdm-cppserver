#include "TcpListener.h"
#include "../log/Logger.h"
#include "NetManager.h"
#include <boost/lexical_cast.hpp>
namespace rdm {

TcpListener::TcpListener(boost::asio::io_service& io_service)
        : io_context_(io_service) {

}

TcpListener::TcpListener(boost::asio::io_service& io_service, const std::string& host, uint16_t port)
        : io_context_(io_service) {
    bind(io_service, host, port);
    startAccept();
}

TcpListener::~TcpListener() {

}

void TcpListener::bind(boost::asio::io_service& io_service, const std::string& host, uint16_t port) {
    address addr = address::from_string(host);
    endpoint_ = std::make_unique<tcp::endpoint>(addr, port);
    accecptor_ = std::make_unique<tcp::acceptor>(io_service, *endpoint_);
}

TcpConn::sptr TcpListener::getConnection(uint32_t conn_id) {
    auto it = conns_.find(conn_id);
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

TcpConn::sptr TcpListener::getConnection() {
    auto it = conns_.begin();
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<TcpConn::sptr> TcpListener::getConnections() {
    std::vector<TcpConn::sptr> cons;
    for (const auto& it : conns_) {
        cons.push_back(it.second);
    }
    return cons;
}

void TcpListener::startAccept() {
    TcpConn::sptr new_connection = TcpConn::create(io_context_);
    accecptor_->async_accept(new_connection->getSocket(),
                             boost::bind(&TcpListener::handleAccept,
                                        this,
                                        new_connection,
                                        boost::asio::placeholders::error));
}

void TcpListener::handleAccept(TcpConn::sptr new_connection,
                               const boost::system::error_code& ec) {
    if (!ec) {
        new_connection->setConnId(NetManager::inst().getConnUid());
        conns_[new_connection->getConnId()] = new_connection;
        LOG_INFO("a client connected id: {}, {}:{}.",
                 new_connection->getConnId(),
                 new_connection->getSocket().remote_endpoint().address().to_string(),
                 new_connection->getSocket().remote_endpoint().port());
        new_connection->start();
    } else {
        LOG_ERROR("{}", ec.message());
        return;
    }

    startAccept();
}

} // namespace rdm