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
    explicit NetClientManager(const std::shared_ptr<Service>& service);
    ~NetClientManager();

    bool init();

    [[nodiscard]] NetClient* getNetClient(uint32_t id) const;
    [[nodiscard]] std::map<uint32_t, NetClient*> getNetClients() const;

private:
    std::map<uint32_t, NetClient*> net_clients_;

    std::weak_ptr<Service> service_;
};

}