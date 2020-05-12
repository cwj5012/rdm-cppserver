#include <iostream>
#include <chrono>

#include <catch2/catch.hpp>

#include "../Hardware.h"

TEST_CASE("Hardware", "[]") {
    std::cout << rdm::hardware_timestamp() << std::endl;
}
