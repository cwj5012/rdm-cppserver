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

    explicit CommandInfo(std::string name,
                std::string desc,
                CommandFunc func)
            : name(std::move(name)),
              desc(std::move(desc)),
              func(std::move(func)) {}
};

class Command {
public:
    explicit Command();
    explicit Command(const std::shared_ptr<Service>& service);

    ~Command();

    bool init();
    void run();
    void release();

    void registCommand(std::unique_ptr<CommandInfo>& cmd_info);
    void registCommand(std::unique_ptr<CommandFunc>& func);
    void parseInput(const std::string& str);
    void executeCommand(const std::string& str);

    static void cmd_help(const std::string& param);
    static void cmd_abort(const std::string& param);
    void cmd_options(const std::string& param);

private:
    /**
     * 初始化基本命令
     * @return
     */
    std::vector<CommandInfo::uptr>& getCommand();

    std::map<std::string, CommandInfo::uptr> command_func_;
    std::vector<std::unique_ptr<CommandFunc>> flag_func_;
    std::weak_ptr<Service> service_;
};

}
