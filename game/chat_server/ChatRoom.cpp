#include "ChatRoom.h"

#include <rdm/log/Logger.h>
#include <rdm/net/NetServer.h>

ChatRoom::ChatRoom(rdm::Service* service, uint64_t id)
        : service_(service), id_(id) {

}

ChatRoom::~ChatRoom() {
    for (auto& item:users_) {
        item.second.reset();
    }
}

void ChatRoom::doOnMessage(const rdm::NetMsg* net_msg) {

}

bool ChatRoom::init() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    service_->getNetServer()->registMessage(101, this);
    service_->getNetServer()->registMessage(102, this);

    return loadData();
}

bool ChatRoom::loadData() {
    return true;
}

void ChatRoom::release() {

}

uint8_t ChatRoom::status() const {
    return 0;
}
