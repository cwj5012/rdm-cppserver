#include "NetManager.h"

namespace rdm {

NetManager::NetManager() {
    mMessageSubject = std::make_shared<MessageSubject>();
}

NetManager::~NetManager() {

}

boost::asio::io_service& NetManager::getService() {
    return io_service_;
}

void NetManager::run() {
    io_service_.run();
}

void NetManager::registMessage(const std::string& message_name, IObserver* observer) {
    mMessageSubject->registObserver(message_name, observer);
}

void NetManager::registMessage(const uint32_t message_type, IObserver* observer) {
    mMessageSubject->registObserver(message_type, observer);
}

std::shared_ptr<MessageSubject> NetManager::getMessageSubject() {
    return mMessageSubject;
}
}