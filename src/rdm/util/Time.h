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
    void restart() {
        reset();
        now_ = high_resolution_clock::now();
    }

    void start() { now_ = high_resolution_clock::now(); }

    void end() { end_ = high_resolution_clock::now(); }

    void reset() {
        now_ = {};
        end_ = {};
    }

    // 单位（秒）
    int64_t durationS() { return duration_cast<std::chrono::seconds>(end_ - now_).count(); }
    // 单位（毫秒）
    int64_t durationMs() { return duration_cast<std::chrono::milliseconds>(end_ - now_).count(); }
    // 单位（微秒）
    int64_t durationUs() { return duration_cast<std::chrono::microseconds>(end_ - now_).count(); }
    // 单位（纳秒）
    int64_t durationNs() { return duration_cast<std::chrono::nanoseconds>(end_ - now_).count(); }

private:
    time_point<steady_clock> now_;
    time_point<steady_clock> end_;
};

}



