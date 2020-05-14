#pragma once

#include <string>
#include <map>
#include <vector>

#include <boost/asio.hpp>

#include "Timer.h"

namespace rdm {

class TimerManager {
public:
    explicit TimerManager(boost::asio::io_service* ios);

    ~TimerManager();

    /**
     * 添加定时器
     * @param id
     * @param delay
     * @param internal
     * @return
     */
    bool add(uint32_t id, int64_t delay, int64_t internal);

    bool add(uint32_t id, int64_t delay, int64_t internal, TimerState state);

    /**
     * 添加定时器
     * @param id
     * @param delay
     * @param internal
     * @param handle
     * @return
     */
    bool add(uint32_t id, int64_t delay, int64_t internal, timerHandle handle);
    bool add(uint32_t id, int64_t delay, int64_t internal, timerHandle handle, TimerState state);

    /**
     * 操作绑定到定时器上
     * @param id
     * @param handle
     * @return
     */
    bool bind(uint32_t id, timerHandle handle);

    /**
     * 暂停定时器
     * 时间不做延长，继续运行定时器以后，如果时间到了，就执行操作
     * 比如：
     *      剩下 10 秒的时候暂停，9 秒后继续，再过 1 秒执行操作
     *      11 秒后继续，则直接执行操作
     * @return
     */
    bool pause(uint32_t id);

    /**
     * 继续定时器
     * @return
     */
    bool keepOn(uint32_t id);

    /**
     * 取消定时器，定时器上绑定的操作，不会执行
     * @param id
     * @return
     */
    bool cancel(uint32_t id);

private:
    boost::asio::io_service* io_service_;

    std::map<uint32_t, Timer*> timers_;
};

}