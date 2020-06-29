#include "NetManager.h"
#include "../log/Logger.h"

namespace rdm {

NetManager::NetManager() {
    message_subject_ = std::make_shared<MessageSubject>();
}

NetManager::~NetManager() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

boost::asio::io_service& NetManager::getService() {
    return io_service_;
}

void NetManager::run() {
    io_service_.run();
}

void NetManager::registMessage(const std::string& message_name, IObserver* observer) {
    message_subject_->registObserver(message_name, observer);
}

void NetManager::registMessage(uint32_t message_type, IObserver* observer) {
    message_subject_->registObserver(message_type, observer);
}

std::shared_ptr<MessageSubject> NetManager::getMessageSubject() {
    return message_subject_;
}

uint32_t NetManager::getConnUid() {
    if (conn_uid_== UINT32_MAX) {
        conn_uid_ = 0;
    }
    return ++conn_uid_;
}

}