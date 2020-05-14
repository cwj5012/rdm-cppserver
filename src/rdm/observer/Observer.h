#pragma once

#include <google/protobuf/message.h>

#include "../net/NetMsg.h"

namespace rdm {

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void doOnMessage(const NetMsg* net_msg) = 0;
};

}