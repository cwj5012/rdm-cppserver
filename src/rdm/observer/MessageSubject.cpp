﻿#include <iostream>
#include <string>

#include "../log/Logger.h"
#include "../observer/MessageSubject.h"
#include "../message/Codec.h"

namespace rdm {

MessageSubject::MessageSubject() {
    mMessageObserverMap.clear();
    mMessageObserverMapByType.clear();
}

MessageSubject::~MessageSubject() {

}

void MessageSubject::registObserver(const std::string& message_name, IObserver* observer) {
    if (observer == nullptr) {
        LOG_ERROR("regist message failed, name: {}", message_name);
        return;
    }

    mMessageObserverMap.insert(std::make_pair(message_name, observer));

    LOG_INFO("regist message, name: {}", message_name);
}

void MessageSubject::registObserver(const MessageResolveType resolve_type, IObserver* observer) {
    if (observer == nullptr) {
        LOG_ERROR("regist message failed, name: {}", static_cast<int32_t>(resolve_type));
        return;
    }

    mMessageObserverMapByType.insert(std::make_pair(resolve_type, observer));

    LOG_INFO("regist message, name: {}", static_cast<int32_t>(resolve_type));
}

void MessageSubject::onChange() {

}

void MessageSubject::onChange(NetMsg* net_msg) {
    if (net_msg == nullptr) {
        LOG_ERROR("net msg is null");
        return;
    }

    auto resolve_type = net_msg->getResolveType();
    switch (resolve_type) {
        case MessageResolveType::BY_PROTOBUF_NAME : {
            auto* pb_msg = decode(*net_msg->getBuf());
            if (pb_msg == nullptr) {
                LOG_ERROR("net msg decode is null, type: {}, size: {}",
                          static_cast<int32_t>(MessageResolveType::BY_PROTOBUF_NAME),
                          net_msg->getBuf()->size());
                return;
            }

            const std::string message_name = pb_msg->GetTypeName();
            // 释放对象
            delete pb_msg;

            auto it = mMessageObserverMap.find(message_name);
            if (it != mMessageObserverMap.end()) {
                mMessageObserverMap[message_name]->doOnMessage(net_msg);
            }
        }
            break;
        case MessageResolveType::BY_PROTOBUF_TYPE : {
            auto* pb_msg = decodeE(*net_msg->getBuf());
            if (pb_msg == nullptr) {
                LOG_ERROR("net msg decode is null, type: {}",
                          static_cast<int32_t>(MessageResolveType::BY_PROTOBUF_TYPE));
                return;
            }

            const std::string message_name = pb_msg->GetTypeName();
            // 释放对象
            delete pb_msg;

            auto it = mMessageObserverMap.find(message_name);
            if (it != mMessageObserverMap.end()) {
                mMessageObserverMap[message_name]->doOnMessage(net_msg);
            }
            break;
        }
        default:
            LOG_ERROR("unknow message resolve type");
            break;
    }


}

void MessageSubject::resolveMessage(NetMsg* net_msg) {
    if (net_msg == nullptr) {
        LOG_ERROR("net msg is null");
        return;
    }

    onChange(net_msg);
}

}