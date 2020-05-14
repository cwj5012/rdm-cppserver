#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

#include <boost/asio.hpp>

namespace rdm {

//using timerHandle = void();
using timerHandle = std::function<void()>;

enum class TimerState {
    RUNNING = 0,
    PAUSE = 1,
    CANCEL = 2
};

/**
 * 定时器
 *
 * 基于 boost::asio::timer 实现
 */
class Timer {
public:

    explicit Timer(boost::asio::io_service* ios,
                   int64_t delay,
                   int64_t internal);

    explicit Timer(boost::asio::io_service* ios,
                   int64_t delay,
                   int64_t internal,
                   TimerState state);

    ~Timer();

    /**
     * 操作绑定到定时器上
     * @param id
     * @param handle
     * @return
     */
    bool bind(timerHandle handle);

    /**
     * 暂停定时器
     * 时间不做延长，继续运行定时器以后，如果时间到了，就执行操作
     * 比如：
     *      剩下 10 秒的时候暂停，9 秒后继续，再过 1 秒执行操作
     *      11 秒后继续，则直接执行操作
     * @return
     */
    bool pause();

    /**
     * 继续定时器
     * @return
     */
    bool keepOn();

    /**
     * 取消定时器，定时器上绑定的操作，不会执行
     * @param id
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

    /**
     * 获取延迟时间
     * @return
     */
    int64_t getDelay() const;

private:
    void handle();

    boost::asio::io_service* io_service_;

    boost::asio::steady_timer* timer_;
    std::vector<timerHandle> handles_;
    TimerState state_;
    int64_t delay_time_;
    int64_t internal_time_;
};

}