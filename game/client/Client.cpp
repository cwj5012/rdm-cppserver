#include "Client.h"
#include "../protocol/MessageType.h"

#include <functional>
#include <memory>

#include <rdm/log/Logger.h>
#include <rdm/command/Command.h>
#include <rdm/command/Options.h>
#include <rdm/net/NetClientManager.h>
#include <rdm/protocol/command.pb.h>
#include <rdm/message/Codec.h>

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

    op_.init();
    op_.add("echo,e", boost::program_options::value<std::string>(), "echo message");
    auto flag = std::make_unique<rdm::CommandFunc>([&](const std::string& arg) {
        if (op_.parse(arg)) {
            auto vm = op_.getValues();
            if (vm.count("command")) {
                LOG_INFO("{}", vm["command"].as<std::string>());

                rdm::pb::Command send_msg;
                send_msg.set_args(vm["command"].as<std::string>());
                for (auto client : this->getClientManager()->getNetClients()) {
                    client.second->write(rdm::encodeE(send_msg, static_cast<uint32_t>(MessageType::kCommand)));
                }
            }

            if (vm.count("echo")) {
                LOG_INFO("{}", vm["echo"].as<std::string>());

                rdm::pb::Echo send_msg;
                send_msg.set_args(vm["echo"].as<std::string>());
                for (auto client : this->getClientManager()->getNetClients()) {
                    client.second->write(rdm::encodeE(send_msg, static_cast<uint32_t>(MessageType::kEcho)));
                }
            }
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
