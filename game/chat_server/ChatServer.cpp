#include "ChatServer.h"

#include <functional>
#include <memory>

#include <rdm/log/Logger.h>
#include <rdm/command/Command.h>
#include <rdm/command/Options.h>

ChatServer::ChatServer() {

}

ChatServer::~ChatServer() {
    std::stringstream ss;
    ss << this;
    LOG_DEBUG("{}, {}", __PRETTY_FUNCTION__, ss.str());
}

bool ChatServer::onInit() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    auto this_ptr = std::dynamic_pointer_cast<ChatServer>(shared_from_this());

    web_command_ = std::make_unique<WebCommand>(this_ptr);
    // web_command_->init();

    auto new_room = std::make_unique<rdm::CommandInfo>(
            "new_room", "create room", [&](const std::string& arg) {
                if (chat_rooms_.find(++room_id_) == chat_rooms_.end()) {
                    chat_rooms_[room_id_] = std::make_unique<ChatRoom>(this_ptr, room_id_);
                    LOG_INFO("add new chat room, id: {}.", room_id_);
                } else {
                    LOG_ERROR("chat room is exist, id: {}.", room_id_);
                }
            });
    getCommand()->registCommand(new_room);

    auto exit = std::make_unique<rdm::CommandInfo>(
            "exit", "exit", [this](const std::string& arg) {
                this->exit();
            });
    getCommand()->registCommand(exit); // std::unique_ptr<CommandFunc>& func

    auto flag = std::make_unique<rdm::CommandFunc>([](const std::string& arg) {
        rdm::Options op;
        op.init();
        if (op.parse(arg)) {
            auto vm = op.getValues();
        }
    });
    getCommand()->registCommand(flag);

    return true;
}

void ChatServer::onRun() {

}

bool ChatServer::onExit() {
    return true;
}
