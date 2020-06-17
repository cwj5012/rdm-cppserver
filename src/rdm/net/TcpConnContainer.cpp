#include "TcpConnContainer.h"

#include "../log/Logger.h"

namespace rdm {

TcpConnContainer::TcpConnContainer() {

}

TcpConnContainer::~TcpConnContainer() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

TcpConn::sptr TcpConnContainer::getServerConnection(uint32_t type, uint32_t id) const {
    auto it = server_connections_.find(type);
    if (it != server_connections_.end()) {
        auto itRes = it->second.find(id);
        if (itRes != it->second.end()) {
            return itRes->second;
        }
    }
    return nullptr;
}

TcpConn::sptr TcpConnContainer::getClientConnection(uint32_t id) const {
    auto it = client_connections_.find(id);
    if (it != client_connections_.end()) {
        return it->second;
    }
    return nullptr;
}

int32_t TcpConnContainer::getServerConnectionCount(uint32_t type) const {
    auto it = server_connections_.find(type);
    if (it != server_connections_.end()) {
        return static_cast<int32_t>(it->second.size());
    }
    return 0;
}

int32_t TcpConnContainer::getClientConnectionCount() const {
    return static_cast<int32_t>(client_connections_.size());
}

bool TcpConnContainer::pushServerConnection(TcpConn::sptr conn, uint32_t type, uint32_t id) {
    if (getServerConnection(type, id)) {
        return false;
    }

    auto it = server_connections_.find(type);
    if (it == server_connections_.end()) {
        std::map<uint32_t, TcpConn::sptr> temp;
        server_connections_[type] = temp;
    }

    // todo weijiechen 检查是不是有问题
    server_connections_[type][id] = conn;
    return true;
}

bool TcpConnContainer::pushClientConnection(TcpConn::sptr conn, uint32_t id) {
    if (getClientConnection(id)) {
        return false;
    }

    client_connections_[id] = conn;
    return true;
}

bool TcpConnContainer::release() {
    server_connections_.clear();
    client_connections_.clear();
    return true;
}

}