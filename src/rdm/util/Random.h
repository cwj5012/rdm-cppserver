/**
 * 随机数生成
 *
 * 算法 MT19937
 */

#pragma once

#include <random>
#include <cstdint>

namespace rdm {

class Random {
public:
    Random();

    Random(uint32_t seed);

    ~Random();

    /**
     * 伪随机整数范围 0 ~ 4294967295 (2^32-1)
     * 随机算法 Linear congruential generator
     * @return
     */
    uint32_t generate();

    /**
     * 伪随机整数范围 min ~ max
     * @param min
     * @param max
     * @return
     */
    int32_t generate(uint32_t min, uint32_t max);

    /**
     * 伪随机浮点数范围 min ~ max
     * @param min
     * @param max
     * @return
     */
    float generatef(float min, float max);

    double generated(double min, double max);

    long double generateld(long double min, long double max);

    /**
     * 设置随机种子
     * @param seed
     */
    void setSeed(uint32_t seed);

private:
    std::random_device device_;
    uint32_t seed_;
    std::mt19937 generator_;
};

}