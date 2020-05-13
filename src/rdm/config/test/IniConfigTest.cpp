#include <catch2/catch.hpp>

#include "../IniConfig.h"

using namespace rdm;

TEST_CASE("IniConfig", "[]") {
    std::string path {"/home/me/test/test.ini"};
    auto ini = IniConfig(path);
    ini.parse();
}