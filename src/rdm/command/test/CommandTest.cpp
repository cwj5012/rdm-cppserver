#include <catch2/catch.hpp>

#include "../Command.h"
#include "../Console.h"
#include "../../log/Logger.h"
#include "../../thread/ThreadUtil.h"

using namespace rdm;

namespace {

void infoFuncA(const std::string& arg) {
    LOG_DEBUG("infoFuncA: {}", arg);
}

}

TEST_CASE("Command-test", "[]") {
//    auto* cmd = new Command();
//    cmd->init();
//    cmd->run();
//
//    CommandInfo infoA("infoA", "infoA desc", infoFuncA);
//    cmd->registCommand(&infoA);
//
//    int i = 0;
//    while (true) {
//        ThreadUtil::sleep(1000);
//        i++;
//        if (i >= 5)
//            break;
//    }
}


