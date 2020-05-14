#pragma once

#include <string>
#include <map>
#include <vector>
#include <cstdint>

#include <boost/asio.hpp>

#include "Timer.h"

namespace rdm {

/**
 * Ticker 类是对 Timer 类的封装
 *
 * 默认为间隔执行的定时器，不支持延迟执行
 */
class Ticker {
public:
    /**
     * 创建 Ticker 定时器，如果 io_service 已经在运行，则会立刻执行一次 handle
     * @param ios
     * @param internal 间隔时间，单位毫秒
     */
    explicit Ticker(boost::asio::io_service* ios, int64_t internal);

    /**
     * 创建 Ticker 定时器，可以设置初始状态，如果设置为 PAUSE，则不会立刻执行一次
     * @param ios
     * @param internal 间隔时间
     * @param state 初始状态
     */
    explicit Ticker(boost::asio::io_service* ios, int64_t internal, TimerState state);

    ~Ticker();

    /**
     * 添加 handle 到容器中，每次 Tick 都会顺序执行容器中的 handle
     * @param handle
     * @return
     */
    bool bind(timerHandle handle);

    /**
     * 暂停
     * @return
     */
    bool pause();

    /**
     * 继续
     * @return
     */
    bool keepOn();

    /**
     * 取消，不会执行容器中的 handle
     * @return
     */
    bool cancel();

    /**
     * 获取容器中的 handle 个数
     * @return
     */
    int32_t getHandleCount() const;

    /**
     * 获取当前状态
     * @return
     */
    TimerState getState() const;

    /**
     * 获取时间间隔
     * @return
     */
    int64_t getInternal() const;

private:
    Timer* timer_;
};

}