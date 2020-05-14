#include "TickerManager.h"

namespace rdm {

TickerManager::TickerManager(boost::asio::io_service* ios)
        : io_service_(ios) {

}

TickerManager::~TickerManager() {

}

bool TickerManager::add(uint32_t id, int64_t internal) {
    return add(id, internal, TimerState::RUNNING);
}

bool TickerManager::add(uint32_t id, int64_t internal, TimerState state) {
    auto it = tickers_.find(id);
    if (it == tickers_.end()) {
        tickers_[id] = new Ticker(io_service_, internal, state);
        return true;
    } else {
        return false;
    }
}

bool TickerManager::add(uint32_t id, int64_t internal, timerHandle handle) {
    return add(id, internal, handle, TimerState::RUNNING);
}

bool TickerManager::add(uint32_t id, int64_t internal, timerHandle handle, TimerState state) {
    auto it = tickers_.find(id);
    if (it == tickers_.end()) {
        tickers_[id] = new Ticker(io_service_, internal, state);
        auto result = tickers_[id]->bind(handle);
        return result;
    } else {
        return false;
    }
}

bool TickerManager::bind(uint32_t id, timerHandle handle) {
    auto it = tickers_.find(id);
    if (it != tickers_.end()) {
        auto result = tickers_[id]->bind(handle);
        return result;
    } else {
        return false;
    }
}

bool TickerManager::pause(uint32_t id) {
    auto it = tickers_.find(id);
    if (it != tickers_.end()) {
        auto result = tickers_[id]->pause();
        return result;
    } else {
        return false;
    }
}

bool TickerManager::keepOn(uint32_t id) {
    auto it = tickers_.find(id);
    if (it != tickers_.end()) {
        auto result = tickers_[id]->keepOn();
        return result;
    } else {
        return false;
    }
}

bool TickerManager::cancel(uint32_t id) {
    auto it = tickers_.find(id);
    if (it != tickers_.end()) {
        auto result = tickers_[id]->cancel();
        if (result) {
            tickers_.erase(it);
        }
        return result;
    } else {
        return false;
    }
}

}