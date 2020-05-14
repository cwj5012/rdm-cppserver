#include "Console.h"
#include "../log/Logger.h"

namespace rdm {

Console::Console()
        : mExit(false) {

}

Console::~Console() {

}

bool Console::init(Command* cmd) {
    if (cmd == nullptr) {
        LOG_ERROR("cmd == nullptr");
        return false;
    }

    mCommand = cmd;
    mThread = std::thread(&Console::getInput, this);
    mThread.detach();

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
    mExit = value;
}

bool Console::getExit() {
    return mExit;
}

}