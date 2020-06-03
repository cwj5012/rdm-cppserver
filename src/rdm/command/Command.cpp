#include "Command.h"
#include "Console.h"
#include "../util/StringUtil.h"
#include "../log/Logger.h"
#include "../service/Service.h"

namespace rdm {

Command::Command() {

}

Command::Command(const std::shared_ptr<Service>& service)
        : service_(service) {

}

Command::~Command() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);


}

bool Command::init() {
    for (auto& item : getCommand()) {
        registCommand(item);
    }

    return true;
}

void Command::run() {
    Console::inst()->init(this);
}

void Command::release() {
    for (auto& item:command_func_) {
        item.second.reset();
    }
}


void Command::registCommand(CommandInfo::uptr& cmd_info) {
    command_func_[cmd_info->name] = std::move(cmd_info);
}

void Command::registCommand(std::unique_ptr<CommandFunc>& func) {
    flag_func_.push_back(std::move(func));
}

void Command::parseInput(const std::string& str) {

}

void Command::executeCommand(const std::string& str) {
    auto result = StringUtil::split(str, " ");

    if (result.empty()) {
        LOG_ERROR("command format error");
        return;
    }

    auto cmd = result[0];
    if (!cmd.empty()) {
        auto it = command_func_.find(cmd);
        if (it != command_func_.end()) {
            command_func_[cmd]->func(str);
        } else {
            LOG_ERROR("command not found: {}", cmd);
        }
    }
}

void Command::cmd_help(const std::string& param) {
    LOG_INFO("cmd_help");
}

void Command::cmd_abort(const std::string& param) {
    LOG_INFO("cmd_abort");
    abort();
}

void Command::cmd_options(const std::string& param) {
    LOG_INFO("cmd_options");
    for (auto& item:flag_func_) {
        (*item)(param);
    }
}

std::vector<CommandInfo::uptr>& Command::getCommand() {
    // static 变量包在函数中，移除 clang 警告
    // initialization with static duration may throw an exception
    static std::vector<CommandInfo::uptr> zCommands{};
    zCommands.push_back(std::move(std::make_unique<CommandInfo>("help", "Display this help", &Command::cmd_help)));
    zCommands.push_back(std::move(std::make_unique<CommandInfo>("abort", "Abort program", &Command::cmd_abort)));
    zCommands.push_back(std::move(std::make_unique<CommandInfo>("/", "opt command", [&](const std::string& arg) {
        this->cmd_options(arg);
    })));

    return zCommands;
}

}