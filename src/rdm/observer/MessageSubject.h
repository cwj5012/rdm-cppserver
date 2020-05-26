#pragma once

#include <string>
#include <map>

#include <google/protobuf/message.h>

#include "../net/NetMsg.h"
#include "../observer/Observer.h"

namespace rdm {

class MessageSubject {
public:
    MessageSubject();
    ~MessageSubject();

    void registObserver(const std::string& message_name, IObserver* observer);

    void registObserver(const uint32_t resolve_type, IObserver* observer);

    void onChange();

    void onChange(NetMsg* net_msg);

    void resolveMessage(NetMsg* net_msg);

private:
    std::map<std::string, IObserver*> mMessageObserverMap;
    std::map<uint32_t, IObserver*> mMessageObserverMapByType;
};

}