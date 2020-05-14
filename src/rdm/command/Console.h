#pragma once

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
        static Console* obj = new Console();
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
    bool mExit;                     // 禁止命令行输入
    Command* mCommand;
    std::string mInputStr;          // 输入字符串
    std::thread mThread;            // 命令行线程
    std::vector<int> mCommandList;  // 命令列表
};

}


