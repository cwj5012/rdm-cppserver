#include "NetAcceptor.h"
#include "../log/Logger.h"

namespace rdm {

NetAcceptor::NetAcceptor(boost::asio::io_service& io_service)
        : io_context_(io_service) {

}

NetAcceptor::NetAcceptor(boost::asio::io_service& io_service, const std::string& addr, uint16_t port)
        : io_context_(io_service) {
    bind(io_service, addr, port);
    startAccept();
}

NetAcceptor::~NetAcceptor() {

}

void NetAcceptor::bind(boost::asio::io_service& io_service, const std::string& addr, uint16_t port) {
    addr_ = std::make_shared<address>();
    addr_->from_string(addr);

    endpoint_ = std::make_shared<tcp::endpoint>(*addr_, port);
    accecptor_ = std::make_shared<tcp::acceptor>(io_service, *endpoint_);
}

NetConnection::sptr NetAcceptor::getConnection(tcp::socket* s) {
    auto it = conns_.find(s);
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

NetConnection::sptr NetAcceptor::getConnection() {
    auto it = conns_.begin();
    if (it != conns_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<NetConnection::sptr> NetAcceptor::getConnections() {
    std::vector<NetConnection::sptr> cons;
    for (auto it : conns_) {
        cons.push_back(it.second);
    }
    return cons;
}

void NetAcceptor::startAccept() {
    NetConnection::sptr new_connection = NetConnection::create(io_context_);
    accecptor_->async_accept(new_connection->getSocket(),
                             boost::bind(&NetAcceptor::handleAccept,
                                        this,
                                        new_connection,
                                        boost::asio::placeholders::error));
}

void NetAcceptor::handleAccept(NetConnection::sptr new_connection,
                               const boost::system::error_code& ec) {
    if (!ec) {
        LOG_INFO("a client connected, {}:{}.",
                 new_connection->getSocket().remote_endpoint().address().to_string(),
                 new_connection->getSocket().remote_endpoint().port());
        conns_[&new_connection->getSocket()] = new_connection;
        new_connection->start();
    } else {
        LOG_ERROR("{}", ec.message());
        return;
    }

    startAccept();
}

} // namespace rdm