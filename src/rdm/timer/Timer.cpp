#include <iostream>

#include <boost/bind.hpp>

#include "Timer.h"
#include "../log/Logger.h"

namespace rdm {

using boost::asio::steady_timer;
using boost::asio::chrono::milliseconds;

Timer::Timer(boost::asio::io_service* ios,
             int64_t delay,
             int64_t internal)
        : io_service_(ios),
          delay_time_(delay),
          internal_time_(internal),
          state_(TimerState::RUNNING) {
    timer_ = new steady_timer(*io_service_, milliseconds(delay_time_));
    timer_->async_wait(boost::bind(&Timer::handle, this));
}

Timer::Timer(boost::asio::io_service* ios,
             int64_t delay,
             int64_t internal,
             TimerState state)
        : io_service_(ios),
          delay_time_(delay),
          internal_time_(internal),
          state_(state) {
    timer_ = new steady_timer(*io_service_, milliseconds(delay_time_));
    timer_->async_wait(boost::bind(&Timer::handle, this));

}

Timer::~Timer() {
    handles_.clear();
}

bool Timer::bind(timerHandle handle) {
    handles_.push_back(handle);
    return true;
}

bool Timer::pause() {
    state_ = TimerState::PAUSE;
    return true;
}

bool Timer::keepOn() {
    state_ = TimerState::RUNNING;
    return true;
}

bool Timer::cancel() {
    boost::system::error_code ec;
    timer_->cancel(ec);
    state_ = TimerState::CANCEL;
    if (!ec) {
        return true;
    }
    LOG_ERROR("Timer::del failure, {}", ec.message());
    return false;
}

int32_t Timer::getHandleCount() const {
    return static_cast<int32_t>(handles_.size());
}

TimerState Timer::getState() const {
    return state_;
}

int64_t Timer::getInternal() const {
    return internal_time_;
}

int64_t Timer::getDelay() const {
    return delay_time_;
}

void Timer::handle() {
    switch (state_) {
        case TimerState::RUNNING: {
            for (auto& handle : handles_) {
                handle();
            }

            if (internal_time_ > 0) {
                // 间隔时间大于零，设置新的定时器
                timer_->expires_at(timer_->expiry() + milliseconds(internal_time_));
                timer_->async_wait(boost::bind(&Timer::handle, this));
            }
            break;
        }
        case TimerState::PAUSE: {
            if (internal_time_ > 0) {
                // 间隔时间大于零，设置新的定时器
                timer_->expires_at(timer_->expiry() + milliseconds(internal_time_));
                timer_->async_wait(boost::bind(&Timer::handle, this));
            }
            break;
        }
        case TimerState::CANCEL: {
            break;
        }
        default: {
            break;
        }
    }
}

}