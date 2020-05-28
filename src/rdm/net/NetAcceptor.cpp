#include "NetAcceptor.h"
#include "../log/Logger.h"

namespace rdm {

NetAcceptor::NetAcceptor(boost::asio::io_service& io_service)
        : mIoContext(io_service) {

}

NetAcceptor::NetAcceptor(boost::asio::io_service& io_service, const std::string& addr, uint16_t port)
        : mIoContext(io_service) {
    bind(io_service, addr, port);
    startAccept();
}

NetAcceptor::~NetAcceptor() {

}

void NetAcceptor::bind(boost::asio::io_service& io_service, const std::string& addr, uint16_t port) {
    mAddress = std::make_shared<address>();
    mAddress->from_string(addr);

    mEndpoint = std::make_shared<tcp::endpoint>(*mAddress, port);
    mAcceptor = std::make_shared<tcp::acceptor>(io_service, *mEndpoint);
}

NetConnection::ptrConnection NetAcceptor::getConnection(tcp::socket* s) {
    auto it = mSocketConnection.find(s);
    if (it != mSocketConnection.end()) {
        return it->second;
    }
    return nullptr;
}

NetConnection::ptrConnection NetAcceptor::getConnection() {
    auto it = mSocketConnection.begin();
    if (it != mSocketConnection.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<NetConnection::ptrConnection> NetAcceptor::getConnections() {
    std::vector<NetConnection::ptrConnection> cons;
    for (auto it : mSocketConnection) {
        cons.push_back(it.second);
    }
    return cons;
}

void NetAcceptor::startAccept() {
    NetConnection::ptrConnection new_connection = NetConnection::create(mIoContext);

    mAcceptor->async_accept(new_connection->getSocket(),
                            boost::bind(&NetAcceptor::handleAccept,
                                        this,
                                        new_connection,
                                        boost::asio::placeholders::error));
}

void NetAcceptor::handleAccept(NetConnection::ptrConnection new_connection,
                               const boost::system::error_code& ec) {
    if (!ec) {
        LOG_INFO("a client connected, {}:{}.",
                 new_connection->getSocket().remote_endpoint().address().to_string(),
                 new_connection->getSocket().remote_endpoint().port());
        mSocketConnection[&new_connection->getSocket()] = new_connection;
        new_connection->start();
    }

    startAccept();
}

} // namespace rdm