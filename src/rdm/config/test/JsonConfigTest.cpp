#include <catch2/catch.hpp>

#include "../JsonConfig.h"

using namespace rdm;

TEST_CASE("JsonConfig", "[]") {
    std::string path {"/home/me/test/test.json"};
    auto json = JsonConfig(path);
    json.parse();
}