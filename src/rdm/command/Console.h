#pragma once

#include <mutex>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "Command.h"

namespace rdm {

class Console {
public:
    Console(Console const&) = delete;              // Copy construct
    Console(Console&&) = delete;                   // Move construct
    Console& operator=(Console const&) = delete;   // Copy assign
    Console& operator=(Console&&) = delete;        // Move assign

    static Console* inst() {
        static auto* obj = new Console();
        return obj;
    }

    bool init(Command* cmd);

    void getInput();

    void setExit(bool value);

    bool getExit();

protected:
    Console();

    ~Console();

private:
    bool exit_{false};              // 禁止命令行输入
    Command* command_;
    std::string input_str_;          // 输入字符串
    std::thread thread_;            // 命令行线程
    std::vector<int> commands_;  // 命令列表
    std::mutex mtx_;
};

}


