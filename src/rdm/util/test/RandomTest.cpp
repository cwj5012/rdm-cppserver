#include <catch2/catch.hpp>

#include "../../log/Logger.h"
#include "../Random.h"

using namespace rdm;

TEST_CASE("Random", "[]") {
    Random r1(1);

    REQUIRE(r1.generate() >= 0);
    REQUIRE(r1.generate() <= 4294967295);

    REQUIRE(r1.generate(1, 10) >= 0);
    REQUIRE(r1.generate(1, 10) <= 10);

    REQUIRE(r1.generatef(0, 1) >= 0);
    REQUIRE(r1.generatef(0, 1) <= 1);

    REQUIRE(r1.generated(0, 1) >= 0);
    REQUIRE(r1.generated(0, 1) <= 1);

    REQUIRE(r1.generateld(0, 1) >= 0);
    REQUIRE(r1.generateld(0, 1) <= 1);
}