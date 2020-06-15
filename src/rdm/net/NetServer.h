#pragma once

#include <memory>

#include "NetManager.h"
#include "NetConnection.h"
#include "NetAcceptor.h"
#include "NetClient.h"

namespace rdm {

class Service;

class NetServer {
public:
    using sptr = std::shared_ptr<Service>;

    explicit NetServer();
    explicit NetServer(const sptr& service);
    ~NetServer();

    void init();
    void run();
    void release();

    void registMessage(uint32_t opcode, IObserver* observer);
    void registMessage(const std::string& message_name, IObserver* observer);

    NetAcceptor::sptr getNetAccept(uint32_t type);

private:
    std::map<uint32_t, NetAcceptor::sptr> mNetAcceptPtr;

    std::weak_ptr<Service> service_;
};

}