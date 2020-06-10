#include <iostream>

#include <cpp_redis/cpp_redis>
#include <catch2/catch.hpp>

#include "../../../util/Time.h"

using namespace rdm;

TEST_CASE("RedisTest", "[]") {
    cpp_redis::client client;

    client.connect();

    client.set("hello", "42");
    client.get("hello", [](cpp_redis::reply& reply) {
        std::cout << reply << std::endl;
    });

    client.sync_commit();
}