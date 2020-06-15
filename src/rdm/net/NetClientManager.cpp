#include "../log/Logger.h"
#include "../config/ServerNetConfig.h"
#include "NetClientManager.h"
#include "NetManager.h"
#include "../thread/ThreadUtil.h"
#include "../message/proto/server_info.pb.h"
#include "../message/Codec.h"
#include "../service/Service.h"

namespace rdm {

NetClientManager::NetClientManager() {

}

NetClientManager::NetClientManager(const std::shared_ptr<Service>& service)
    : service_(service) {

}

NetClientManager::~NetClientManager() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool NetClientManager::init() {
    NetManager& nm = NetManager::inst();

    auto info = service_.lock()->getServerNetConfig()->getServerNetInfo();
    LOG_INFO("===================== connect to remote...");
    for (auto& item : info->connect_list) {
        auto id = item.first;
        auto ip = item.second.ip;
        auto port = item.second.port;
        // NetClient 是异步连接，是否连接成功，在后面判断
        auto* client = new NetClient(&nm.getService(), ip, port);
        net_clients_[id] = client;
    }

    while (true) {
        // todo 等待 1 秒检查连接远程服务器是否成功，如果不是内网连接，等待时间配大点，比如 3 秒
        ThreadUtil::sleep(1000);
        bool all_connected = true;
        for (auto& item : info->connect_list) {
            auto id = item.first;
            auto ip = item.second.ip;
            auto port = item.second.port;
            if (!net_clients_[id]->isConnected()) {
                // LOG_ERROR("the server is not connected, try connect to {}:{} again", ip, port);
                all_connected = false;
                net_clients_[id]->doConnect();
            }
        }
        if (all_connected) {
            LOG_INFO("all server is connected");
            break;
        }
    }

    rdm::pb::ServerRegister send_msg;
    send_msg.set_id(info->system_id);
    send_msg.set_type(info->system_type);
    for (auto client : net_clients_) {
        // todo cwj
        // 连接上服务器以后，会发一条自己的信息通知服务器
        // client.second->write(encodeE(send_msg));
    }
    LOG_INFO("notify other server the id and type info");

    return true;
}

NetClient* NetClientManager::getNetClient(uint32_t id) const {
    auto it = net_clients_.find(id);
    if (it != net_clients_.end()) {
        return it->second;
    }
    return nullptr;
}

std::map<uint32_t, NetClient*> NetClientManager::getNetClients() const {
   return net_clients_;
}

}