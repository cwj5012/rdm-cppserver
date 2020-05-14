#pragma once

#include <utility>
#include <vector>

#include <string>
#include <map>

namespace rdm {

using CommandFunc = void (*)(const std::string& arg);

struct CommandInfo {
    std::string name;
    std::string desc;
    CommandFunc func;

    CommandInfo(std::string name,
                std::string desc,
                CommandFunc func)
            : name(std::move(name)),
              desc(std::move(desc)),
              func(func) {}
};

class Command {
public:
    Command();

    ~Command();

    bool init();

    void run();

    void registCommand(const CommandInfo* cmd_info);

    void parseInput(const std::string& str);

    void executeCommand(const std::string& str);

    static void cmd_help(const std::string& param);

    static void cmd_exit(const std::string& param);

    static void cmd_quit(const std::string& param);

private:
    /**
     * 初始化基本命令
     * @return
     */
    std::vector<CommandInfo>& getCommand();

    std::map<std::string, const CommandInfo*> mCommandFunc;
};

}
