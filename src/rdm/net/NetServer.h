#pragma once

#include <memory>

#include "NetManager.h"
#include "NetConnection.h"
#include "NetAcceptor.h"
#include "NetClient.h"

namespace rdm {

class NetServer {
public:
    explicit NetServer();

    ~NetServer();

    static NetServer& inst() {
        static NetServer obj;
        return obj;
    }

    void init();

    void run();

    void release();

    void registMessage(const uint32_t opcode, IObserver* observer);
    void registMessage(const std::string& message_name, IObserver* observer);

    std::shared_ptr<NetAcceptor> getNetAccept(uint32_t type);

private:
    std::map<uint32_t, std::shared_ptr<NetAcceptor>> mNetAcceptPtr;

};

}