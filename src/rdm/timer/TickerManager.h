#pragma once

#include <string>
#include <map>
#include <vector>

#include <boost/asio.hpp>

#include "Ticker.h"

namespace rdm {

class TickerManager {
public:
    explicit TickerManager(boost::asio::io_service* ios);

    ~TickerManager();

    /**
     * 创建一个 Ticker，初始状态为 RUNNING
     * @param id
     * @param internal
     * @return
     */
    bool add(uint32_t id, int64_t internal);

    /**
     * 创建一个 Ticker，设置初始状态
     * @param id
     * @param internal
     * @param state
     * @return
     */
    bool add(uint32_t id, int64_t internal, TimerState state);

    /**
     * 创建一个 Ticker，初始状态为 RUNNING
     * @param id
     * @param internal
     * @param handle
     * @return
     */
    bool add(uint32_t id, int64_t internal, timerHandle handle);

    /**
     * 创建一个 Ticker，设置初始状态
     * @param id
     * @param internal
     * @param handle
     * @param state
     * @return
     */
    bool add(uint32_t id, int64_t internal, timerHandle handle, TimerState state);

    /**
     * 绑定 handle 到定时器上
     * @param id
     * @param handle
     * @return
     */
    bool bind(uint32_t id, timerHandle handle);

    /**
     * 暂停
     * @param id
     * @return
     */
    bool pause(uint32_t id);

    /**
     * 继续
     * @param id
     * @return
     */
    bool keepOn(uint32_t id);

    /**
     * 取消
     * @param id
     * @return
     */
    bool cancel(uint32_t id);

private:
    boost::asio::io_service* io_service_;

    std::map<uint32_t, Ticker*> tickers_;
};

}