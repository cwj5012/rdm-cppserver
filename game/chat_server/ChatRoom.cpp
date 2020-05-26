#include "ChatRoom.h"

#include <rdm/log/Logger.h>
#include <rdm/net/NetServer.h>
#include <rdm/service/Service.h>

ChatRoom::ChatRoom(rdm::Service* service)
        : service_(service) {

}

ChatRoom::~ChatRoom() {

}

void ChatRoom::doOnMessage(const rdm::NetMsg* net_msg) {

}

bool ChatRoom::init() {
    LOG_INFO("ChatRoom::init");

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
