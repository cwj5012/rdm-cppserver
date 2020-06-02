#pragma once

#include <cstdint>
#include <chrono>
#include "../core/NonCopyable.h"

namespace rdm {

class Time : NonCopyable {
public:
    Time() = delete;
    ~Time() = default;

    static int64_t getTimeStamp();
};

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

class StopWatch {
public:
    void start() { now_ = high_resolution_clock::now(); }

    void end() { end_ = high_resolution_clock::now(); }

    void reset() {
        now_ = {};
        end_ = {};
    }

    int64_t duration() { return duration_cast<std::chrono::milliseconds>(end_ - now_).count(); }

private:
    time_point<steady_clock> now_;
    time_point<steady_clock> end_;
};

}



