#include <catch2/catch.hpp>

#include "../Console.h"
#include "../Command.h"

using namespace rdm;

TEST_CASE("Console-test", "[]") {
    Command* cmd = new Command();
    Console::inst()->init(cmd);
}