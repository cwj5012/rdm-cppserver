#include "Client.h"

#include <functional>
#include <memory>

#include <rdm/log/Logger.h>
#include <rdm/command/Command.h>
#include <rdm/command/Options.h>

Client::Client() {

}

Client::~Client() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool Client::onInit() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

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

void Client::onRun() {

}

bool Client::onExit() {
    return true;
}
