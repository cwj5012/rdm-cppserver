#pragma once

#include <cstdint>

namespace rdm {

class ThreadUtil {
public:
    ThreadUtil() = delete;

    ~ThreadUtil() = default;

    static void sleep(int32_t millisecond);
};

}