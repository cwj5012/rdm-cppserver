#pragma once

#include <utility>
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include <map>

namespace rdm {

class Service;

// 下面的代码不行，要用 std::function
// using CommandFunc = void (*)(const std::string& arg);
using CommandFunc = std::function<void(const std::string& arg)>;

struct CommandInfo {
    using uptr = std::unique_ptr<CommandInfo>;

    std::string name;
    std::string desc;
    CommandFunc func;

    CommandInfo(std::string name,
                std::string desc,
                CommandFunc func)
            : name(std::move(name)),
              desc(std::move(desc)),
              func(std::move(func)) {}
};

class Command {
public:
    explicit Command(Service* service);

    ~Command();

    bool init();
    void run();

    void registCommand(std::unique_ptr<CommandInfo>& cmd_info);
    void parseInput(const std::string& str);
    void executeCommand(const std::string& str);

    static void cmd_help(const std::string& param);
    static void cmd_exit(const std::string& param);

private:
    /**
     * 初始化基本命令
     * @return
     */
    std::vector<CommandInfo::uptr>& getCommand();

    std::map<std::string, CommandInfo::uptr> mCommandFunc;

    std::shared_ptr<Service> service_;
};

}
