#include <catch2/catch.hpp>

#include "../Time.h"

using namespace rdm;

TEST_CASE("Time", "[]") {
    // 时间戳范围 2019-01-01 ~ 2099-01-01
    const int64_t nTime = Time::getTimeStamp();
    REQUIRE(nTime > 1546272000);
    REQUIRE(nTime < 4070880000);
}