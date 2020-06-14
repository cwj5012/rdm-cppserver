#include <iostream>

#include <cpp_redis/cpp_redis>
#include <catch2/catch.hpp>

#include "../../../util/Time.h"

using namespace rdm;

TEST_CASE("RedisTest", "[]") {
    cpp_redis::client client;

    client.connect("ubuntu.a.com", 6379);

    StopWatch sw;
    sw.start();
    for (int i = 0; i < 10 * 1000; ++i) {
        client.set(std::to_string(i), "42");
    }
    sw.end();
    std::cout << "insert_one 1w, " << sw.durationMs() << " ms" << std::endl;
    sw.reset();

    client.set("hello", "world");
    client.get("hello", [](cpp_redis::reply& reply) {
        std::cout << reply << std::endl;
    });

    client.sync_commit();
}