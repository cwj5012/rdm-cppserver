#include "Client.h"
#include "MessageType.h"

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

    auto flag = std::make_unique<rdm::CommandFunc>([&](const std::string& arg) {
        rdm::Options op;
        op.init();
        if (op.parse(arg)) {
            auto vm = op.getValues();
            if (vm.count("command")) {
                LOG_INFO("{}", vm["command"].as<std::string>());

                rdm::pb::Command send_msg;
                send_msg.set_args(vm["command"].as<std::string>());
                for (auto client : this->getClientManager()->getNetClients()) {
                    // 连接上服务器以后，会发一条自己的信息通知服务器
                    client.second->write(rdm::encodeE(send_msg, static_cast<uint32_t>(MessageType::kCommand)));
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
