#include "Command.h"
#include "Console.h"
#include "../util/StringUtil.h"
#include "../log/Logger.h"

namespace rdm {

Command::Command() {

}

Command::~Command() {

}

bool Command::init() {
    for (auto& item : getCommand()) {
        registCommand(&item);
    }

    return true;
}

void Command::run() {
    Console::inst()->init(this);
}

std::vector<CommandInfo>& Command::getCommand() {
    // static 变量包在函数中，移除 clang 警告
    // initialization with static duration may throw an exception
    static std::vector<CommandInfo> zCommands = {
            {"help", "Display this help",                 &Command::cmd_help,},
            {"exit", "Shutdown server (save data)",       &Command::cmd_exit,},
            {"quit", "Shutdown server (don't save data)", &Command::cmd_quit,},
    };
    return zCommands;
}

void Command::registCommand(const CommandInfo* cmd_info) {
    mCommandFunc[cmd_info->name] = cmd_info;
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
    auto it = mCommandFunc.find(cmd);
    if (it != mCommandFunc.end()) {
        LOG_INFO("{}", cmd);
        mCommandFunc[cmd]->func(str);
    } else {
        LOG_ERROR("command not found: {}", cmd);
    }
}

void Command::cmd_help(const std::string& param) {
    LOG_INFO("cmd_help");
}

void Command::cmd_exit(const std::string& param) {
    LOG_INFO("cmd_exit");
}

void Command::cmd_quit(const std::string& param) {
    LOG_INFO("cmd_quit");
}

}