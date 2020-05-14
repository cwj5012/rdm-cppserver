#include <catch2/catch.hpp>

#include "../IniConfig.h"

using namespace rdm;

TEST_CASE("IniConfig", "[]") {
    std::string path{"/home/me/test/test.ini"};
    auto ini = IniConfig(path);
    ini.parse();
    auto reader = ini.getReader();

    REQUIRE(reader->GetInteger("protocol", "version", -1) == 6);
    REQUIRE(reader->Get("user", "name", "UNKNOWN") == "Bob Smith");
    REQUIRE(reader->Get("user", "email", "UNKNOWN") == "bob@smith.com");
    REQUIRE(reader->GetReal("user", "pi", -1) == 3.14159);
    REQUIRE(reader->GetBoolean("user", "active", true));
}