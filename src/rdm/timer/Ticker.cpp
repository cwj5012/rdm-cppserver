#include <iostream>

#include "Ticker.h"
#include "Timer.h"

namespace rdm {

using boost::asio::steady_timer;
using boost::asio::chrono::milliseconds;

Ticker::Ticker(boost::asio::io_service* ios, int64_t internal) {
    timer_ = new Timer(ios, 0, internal);
}

Ticker::Ticker(boost::asio::io_service* ios, int64_t internal, TimerState state) {
    timer_ = new Timer(ios, 0, internal, state);
}

Ticker::~Ticker() {

}

bool Ticker::bind(timerHandle handle) {
    return timer_->bind(handle);
}

bool Ticker::pause() {
    return timer_->pause();
}

bool Ticker::keepOn() {
    return timer_->keepOn();
}

bool Ticker::cancel() {
    return timer_->cancel();
}

int32_t Ticker::getHandleCount() const {
    return timer_->getHandleCount();
}

TimerState Ticker::getState() const {
    return timer_->getState();
}

int64_t Ticker::getInternal() const {
    return timer_->getInternal();
}

}