#include "ApiService.h"

#include <functional>
#include <memory>

#include <rdm/log/Logger.h>
#include <rdm/command/Command.h>
#include <rdm/command/Options.h>

ApiService::ApiService() {

}

ApiService::~ApiService() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool ApiService::onInit() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    auto this_ptr = std::dynamic_pointer_cast<ApiService>(shared_from_this());

    web_command_ = std::make_unique<WebCommand>(this_ptr);
    web_command_->init();

    auto new_room = std::make_unique<rdm::CommandInfo>(
            "new_room", "create room", [&](const std::string& arg) {
                if (chat_rooms_.find(++room_id_) != chat_rooms_.end()) {
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

    op_.init();
    op_.add("echo,e", boost::program_options::value<std::string>(), "echo message");
    auto flag = std::make_unique<rdm::CommandFunc>([&](const std::string& arg) {
        if (op_.parse(arg)) {
            auto vm = op_.getValues();
            if (vm.count("command")) {
                LOG_INFO("{}", vm["command"].as<std::string>());
            }
        }
    });
    getCommand()->registCommand(flag);



    return true;
}

void ApiService::onRun() {

}

bool ApiService::onExit() {
    return true;
}
