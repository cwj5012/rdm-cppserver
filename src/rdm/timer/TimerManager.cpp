#include "TimerManager.h"

namespace rdm {

TimerManager::TimerManager(boost::asio::io_service* ios)
        : io_service_(ios) {

}

TimerManager::~TimerManager() {

}

bool TimerManager::add(uint32_t id,
                       int64_t delay,
                       int64_t internal) {

    return add(id, delay, internal, TimerState::RUNNING);
}

bool TimerManager::add(uint32_t id,
                       int64_t delay,
                       int64_t internal,
                       TimerState state) {

    auto it = timers_.find(id);
    if (it == timers_.end()) {
        timers_[id] = new Timer(io_service_, delay, internal, state);
        return true;
    } else {
        return false;
    }
}

bool TimerManager::add(uint32_t id,
                       int64_t delay,
                       int64_t internal,
                       timerHandle handle) {

    return add(id, delay, internal, handle, TimerState::RUNNING);
}

bool TimerManager::add(uint32_t id,
                       int64_t delay,
                       int64_t internal,
                       timerHandle handle,
                       TimerState state) {

    auto it = timers_.find(id);
    if (it == timers_.end()) {
        timers_[id] = new Timer(io_service_, delay, internal, state);
        auto result = timers_[id]->bind(handle);
        return result;
    } else {
        return false;
    }
}

bool TimerManager::bind(uint32_t id, timerHandle handle) {
    auto it = timers_.find(id);
    if (it != timers_.end()) {
        auto result = timers_[id]->bind(handle);
        return result;
    } else {
        return false;
    }
}

bool TimerManager::pause(uint32_t id) {
    auto it = timers_.find(id);
    if (it != timers_.end()) {
        auto result = timers_[id]->pause();
        return result;
    } else {
        return false;
    }
}

bool TimerManager::keepOn(uint32_t id) {
    auto it = timers_.find(id);
    if (it != timers_.end()) {
        auto result = timers_[id]->keepOn();
        return result;
    } else {
        return false;
    }
}

bool TimerManager::cancel(uint32_t id) {
    auto it = timers_.find(id);
    if (it != timers_.end()) {
        auto result = timers_[id]->cancel();
        if (result) {
            timers_.erase(it);
        }
        return result;
    } else {
        return false;
    }
}

}