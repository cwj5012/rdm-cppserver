#pragma once

#include <map>
#include <string>
#include <cstdint>

#include "NetClient.h"

namespace rdm {

class Service;

class NetClientManager {
public:
    NetClientManager();
    NetClientManager(const std::shared_ptr<Service>& service);
    ~NetClientManager();

    bool init();

    NetClient* getNetClient(uint32_t id);

private:
    std::map<uint32_t, NetClient*> net_clients_;

    std::weak_ptr<Service> service_;
};

}