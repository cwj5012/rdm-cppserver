#pragma once

#include <map>
#include <string>
#include <cstdint>

#include "NetClient.h"

namespace rdm {

class NetClientManager {
public:
    NetClientManager();

    ~NetClientManager();

    bool init();

    NetClient* getNetClient(uint32_t id);

private:
    std::map<uint32_t, NetClient*> net_clients_;
};

}