#include <catch2/catch.hpp>

#include "../Logger.h"

TEST_CASE("Logger", "[console]")
{
    LOG_TRACE("trace message");
    LOG_DEBUG("debug message");
    LOG_INFO("info message");
    // LOG_WARN("warn message");
    // LOG_ERROR("error message");
}