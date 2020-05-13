#include <chrono>
#include <thread>

#include "ThreadUtil.h"

namespace rdm {

void ThreadUtil::sleep(int32_t millisecond) {
    std::chrono::milliseconds dura(millisecond);
    std::this_thread::sleep_for(dura);
}

}