#include "Command.h"
#include "Console.h"
#include "../util/StringUtil.h"
#include "../log/Logger.h"
#include "../service/Service.h"

namespace rdm {

Command::Command(Service* service)
        : service_(service) {

}

Command::~Command() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    for (auto& item:mCommandFunc) {
        item.second.reset();
    }

    Console::inst()->setExit(true);
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


void Command::registCommand(CommandInfo::uptr& cmd_info) {
    mCommandFunc[cmd_info->name] = std::move(cmd_info);
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
        auto it = mCommandFunc.find(cmd);
        if (it != mCommandFunc.end()) {
            mCommandFunc[cmd]->func(str);
        } else {
            LOG_ERROR("command not found: {}", cmd);
        }
    }
}

void Command::cmd_help(const std::string& param) {
    LOG_INFO("cmd_help");
}

void Command::cmd_exit(const std::string& param) {
    LOG_INFO("cmd_exit");
}

std::vector<CommandInfo::uptr>& Command::getCommand() {
    // static 变量包在函数中，移除 clang 警告
    // initialization with static duration may throw an exception
    static std::vector<CommandInfo::uptr> zCommands{};
    zCommands.push_back(std::move(
            std::make_unique<CommandInfo>("help", "Display this help", &Command::cmd_help))
    );
    return zCommands;
}

}