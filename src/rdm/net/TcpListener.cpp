#include "TcpListener.h"
#include "../log/Logger.h"
#include "NetManager.h"

namespace rdm {

TcpListener::TcpListener(boost::asio::io_service& io_service)
        : io_context_(io_service) {

}

TcpListener::TcpListener(boost::asio::io_service& io_service, const std::string& addr, uint16_t port)
        : io_context_(io_service) {
    bind(io_service, addr, port);
    startAccept();
}

TcpListener::~TcpListener() {

}

void TcpListener::bind(boost::asio::io_service& io_service, const std::string& addr, uint16_t port) {
    addr_ = std::make_shared<address>();
    addr_->from_string(addr);

    endpoint_ = std::make_shared<tcp::endpoint>(*addr_, port);
    accecptor_ = std::make_shared<tcp::acceptor>(io_service, *endpoint_);
}

NetConnection::sptr TcpListener::getConnection(uint32_t conn_id) {
    auto it = conns_.find(conn_id);
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

NetConnection::sptr TcpListener::getConnection() {
    auto it = conns_.begin();
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<NetConnection::sptr> TcpListener::getConnections() {
    std::vector<NetConnection::sptr> cons;
    for (const auto& it : conns_) {
        cons.push_back(it.second);
    }
    return cons;
}

void TcpListener::startAccept() {
    NetConnection::sptr new_connection = NetConnection::create(io_context_);
    accecptor_->async_accept(new_connection->getSocket(),
                             boost::bind(&TcpListener::handleAccept,
                                        this,
                                        new_connection,
                                        boost::asio::placeholders::error));
}

void TcpListener::handleAccept(NetConnection::sptr new_connection,
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