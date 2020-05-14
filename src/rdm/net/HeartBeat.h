#pragma once

#include <cstdint>

namespace rdm {

class HeartBeat {
public:
    HeartBeat();

    ~HeartBeat() = default;

    /**
     * 是否存活，无响应次数超过上限
     * @return
     */
    bool isDie() const;

    /**
     * 设置存活状态
     * @param alive
     */
    void setAlive(bool alive);

    /**
     * 获取存活状态
     * @return
     */
    bool isAlive() const;

    /**
     * 获取无响应次数
     * @return
     */
    int8_t dieCount() const;

    /**
     * 设置重试次数上限
     */
    void setMaxTryNum(int8_t max_num);

    /**
     * 获取重试次数上限
     * @return
     */
    int8_t getMaxTryNum() const;

private:
    bool is_alive_;               // 上次心跳检查是否存活
    int8_t die_count_;            // 连续无响应次数
    static int8_t max_try_num_;   // 重试次数上限
};

}




