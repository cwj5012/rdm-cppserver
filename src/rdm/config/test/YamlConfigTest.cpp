#include <catch2/catch.hpp>

#include "../YamlConfig.h"
#include "../../log/Logger.h"

using namespace rdm;

TEST_CASE("YamlConfig", "[]") {
    std::string path{"../../src/rdm/config/test/test.yaml"};
    auto yaml = YamlConfig(std::move(path));
    REQUIRE(yaml.parse() == 0);
    auto node = yaml.getNode();
    if (!node->IsNull()) {
        REQUIRE((*node)["server"]["id"].as<int>() == 1);
        REQUIRE((*node)["server"]["name"].as<std::string>() == "chat_room");

        REQUIRE((*node)["listen"][0]["id"].as<int>() == 1);
        REQUIRE((*node)["listen"][0]["ip"].as<std::string>() == "127.0.0.1");
        REQUIRE((*node)["listen"][0]["port"].as<int>() == 6001);

        REQUIRE((*node)["listen"][1]["id"].as<int>() == 2);
        REQUIRE((*node)["listen"][1]["ip"].as<std::string>() == "127.0.0.1");
        REQUIRE((*node)["listen"][1]["port"].as<int>() == 6002);

        REQUIRE((*node)["connect"][0]["id"].as<int>() == 1);
        REQUIRE((*node)["connect"][0]["ip"].as<std::string>() == "127.0.0.1");
        REQUIRE((*node)["connect"][0]["port"].as<int>() == 6051);

        REQUIRE((*node)["db"]["mysql"]["host"].as<std::string>() == "127.0.0.1");
        REQUIRE((*node)["db"]["mysql"]["port"].as<int>() == 3306);
        REQUIRE((*node)["db"]["mysql"]["user"].as<std::string>() == "root");
        REQUIRE((*node)["db"]["mysql"]["passwd"].as<std::string>() == "1234");
        REQUIRE((*node)["db"]["mysql"]["schema"].as<std::string>() == "cx");
    }
}