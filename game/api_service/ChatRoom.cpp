#include "ChatRoom.h"

#include <rdm/log/Logger.h>
#include <rdm/net/NetServer.h>

#include "MessageType.h"
#include "ApiService.h"

ChatRoom::ChatRoom(const std::shared_ptr<ApiService>& service, uint64_t id)
        : service_(service),
          id_(id) {

}

ChatRoom::~ChatRoom() {
    for (auto& item:users_) {
        item.second.reset();
    }
}

void ChatRoom::doOnMessage(const rdm::NetMsg* net_msg) {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool ChatRoom::init() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    service_.lock()->getNetServer()->registMessage(static_cast<uint32_t>(MessageType::kCommand), this);
    service_.lock()->getNetServer()->registMessage(static_cast<uint32_t>(MessageType::kNone), this);

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
