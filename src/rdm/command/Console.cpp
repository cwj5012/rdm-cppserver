#include "Console.h"
#include "../log/Logger.h"

namespace rdm {

Console::Console() {

}

Console::~Console() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    mThread.join();
}

bool Console::init(Command* cmd) {
    if (cmd == nullptr) {
        LOG_ERROR("cmd == nullptr");
        return false;
    }

    mCommand = cmd;
    mThread = std::thread(&Console::getInput, this);

    return true;
}

void Console::getInput() {
    while (true) {
        std::string str;
        std::getline(std::cin, str);

        if (mExit) {
            break;
        } else {
            mCommand->executeCommand(str);
        }
    }
}

void Console::setExit(bool value) {
    std::lock_guard<std::mutex> lck(mtx_);
    mExit = value;
}

bool Console::getExit() {
    return mExit;
}

}