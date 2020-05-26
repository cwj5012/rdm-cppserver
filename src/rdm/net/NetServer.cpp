#include "../config/ServerNetConfig.h"
#include "NetServer.h"
#include "../log/Logger.h"

namespace rdm {

NetServer::NetServer() {

}

NetServer::~NetServer() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
    release();
}


void NetServer::init() {
    NetManager& nm = NetManager::inst();

    auto info = ServerNetConfig::inst()->getServerNetInfo();
    LOG_INFO("=====================");
    for (auto& item : info->listen_list) {
        auto id = item.first;
        auto ip = item.second.ip;
        auto port = item.second.port;
        mNetAcceptPtr[id] = std::make_shared<NetAcceptor>(nm.getService(), ip, std::stoi(port));

        LOG_INFO("listen, id:{} host: {}:{}", id, ip, port);
    }

}

void NetServer::run() {
    NetManager& nm = NetManager::inst();
    nm.getService().run();
}

void NetServer::release() {
    mNetAcceptPtr.clear();

    NetManager& nm = NetManager::inst();
    nm.getService().stop();
}

void NetServer::registMessage(const uint32_t opcode, IObserver* observer) {
    NetManager::inst().registMessage(opcode, observer);
}

void NetServer::registMessage(const std::string& message_name, IObserver* observer) {
    NetManager::inst().registMessage(message_name, observer);
}

std::shared_ptr<NetAcceptor> NetServer::getNetAccept(uint32_t type) {
    auto it = mNetAcceptPtr.find(type);
    if (it != mNetAcceptPtr.end()) {
        return mNetAcceptPtr[type];
    }
    return nullptr;
}



}