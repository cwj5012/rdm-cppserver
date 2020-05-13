#include <catch2/catch.hpp>

#include "../StringUtil.h"

using namespace rdm;

TEST_CASE("StringUtil-split", "[]") {
    auto result = StringUtil::split("123,456 abc efg", " ");
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "123,456");
    REQUIRE(result[1] == "abc");
    REQUIRE(result[2] == "efg");
}

TEST_CASE("StringUtil-charToBinary", "[]") {
    char ch1 = 'a';
    auto result = StringUtil::charToBinary('a');
    REQUIRE(result == "01100001");
}