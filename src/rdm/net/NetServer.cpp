#include "../config/ServerNetConfig.h"
#include "NetServer.h"
#include "../log/Logger.h"
#include "../service/Service.h"

namespace rdm {

NetServer::NetServer() {

}

NetServer::NetServer(const sptr& service)
        : service_(service) {

}

NetServer::~NetServer() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

void NetServer::init() {
    NetManager& nm = NetManager::inst();
    auto info = service_.lock()->getServerNetConfig()->getServerNetInfo();
    LOG_INFO("===================== listen from remote...");
    for (auto& item : info->listen_list) {
        auto id = item.first;
        auto ip = item.second.ip;
        auto port = item.second.port;
        try {
            tcp_listeners_[id] = std::make_shared<TCPListener>(nm.getService(), ip, std::stoi(port));
        } catch (std::exception& ex) {
            LOG_ERROR("{}：{}, {}", ip, port, ex.what());
            abort();
        }
        LOG_INFO("listen, id:{}, host: {}:{}", id, ip, port);
    }
}

void NetServer::run() {
    NetManager& nm = NetManager::inst();
    nm.getService().run();
}

void NetServer::release() {
    tcp_listeners_.clear();

    NetManager& nm = NetManager::inst();
    nm.getService().stop();
}

void NetServer::registMessage(uint32_t opcode, IObserver* observer) {
    NetManager::inst().registMessage(opcode, observer);
}

void NetServer::registMessage(const std::string& message_name, IObserver* observer) {
    NetManager::inst().registMessage(message_name, observer);
}

TCPListener::sptr NetServer::getNetAccept(uint32_t type) {
    auto it = tcp_listeners_.find(type);
    if (it != tcp_listeners_.end()) {
        return tcp_listeners_[type];
    }
    return nullptr;
}

}