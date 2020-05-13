#pragma once

#include <cstdint>
#include "../core/NonCopyable.h"

namespace rdm {

class Time : NonCopyable {
public:
    Time() = delete;

    ~Time() = default;

    static int64_t getTimeStamp();
};

}



