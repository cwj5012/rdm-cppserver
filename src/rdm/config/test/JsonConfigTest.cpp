#include <catch2/catch.hpp>

#include "../JsonConfig.h"
#include "../../log/Logger.h"

using namespace rdm;

TEST_CASE("JsonConfig", "[]") {
    std::string path{"../../src/rdm/config/test/test.json"};
    auto json = JsonConfig(path);
    json.parse();
    auto root = json.getRoot();

    REQUIRE(root.get("my-encoding", "").asString() == "UTF-8");

    REQUIRE(root["my-plug-ins"].get(0u, "").asString() == "python");
    REQUIRE(root["my-plug-ins"].get(1, "").asString() == "c++");
    REQUIRE(root["my-plug-ins"].get(2, "").asString() == "ruby");

    REQUIRE(root["my-indent"].get("length", 1).asInt() == 3);
    REQUIRE(root["my-indent"].get("use_space", false).asBool());
}
