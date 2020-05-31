#include <ctime>
#include <chrono>

#include <catch2/catch.hpp>

#include "../ThreadUtil.h"

using namespace rdm;

TEST_CASE("ThreadUtil", "[sleep]") {
    auto unix_timestamp_begin = std::chrono::seconds(std::time(nullptr));
    ThreadUtil::sleep(1000);
    auto unix_timestamp_end = std::chrono::seconds(std::time(nullptr));
    REQUIRE(unix_timestamp_end.count() - unix_timestamp_begin.count() == 1);

    unix_timestamp_begin = std::chrono::seconds(std::time(nullptr));
    ThreadUtil::sleep(2000);
    unix_timestamp_end = std::chrono::seconds(std::time(nullptr));
    REQUIRE(unix_timestamp_end.count() - unix_timestamp_begin.count() == 2);
}