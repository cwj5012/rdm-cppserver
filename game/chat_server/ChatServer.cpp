#include "ChatServer.h"

 #include <functional>
#include <memory>

#include <rdm/log/Logger.h>
#include <rdm/command/Command.h>

ChatServer::ChatServer() {

}

ChatServer::~ChatServer() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}


bool ChatServer::onInit() {
    LOG_INFO("ChatServer::onInit");

    auto new_room = std::make_unique<rdm::CommandInfo>(
            "new_room", "create room", std::bind(&ChatServer::newChatRoom, this, std::placeholders::_1));

    getCommand()->registCommand(new_room);

    auto exit = std::make_unique<rdm::CommandInfo>(
            "exit", "exit", [this](const std::string& arg) {
                this->exit();
            });

    getCommand()->registCommand(exit);

    return true;
}

void ChatServer::onRun() {

}

bool ChatServer::onExit() {
    return true;
}

void ChatServer::newChatRoom(const std::string& arg) {
    LOG_INFO("add new chat room.");

    if (chat_rooms_.find(++room_id_) != chat_rooms_.end()) {
        chat_rooms_[room_id_] = std::make_unique<ChatRoom>(this, room_id_);
    }
}
