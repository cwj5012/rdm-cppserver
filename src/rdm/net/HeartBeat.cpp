#include "HeartBeat.h"

namespace rdm {

int8_t HeartBeat::max_try_num_ = 1;

HeartBeat::HeartBeat()
        : is_alive_(true),
          die_count_(0) {}

bool HeartBeat::isDie() const {
    return die_count_ >= HeartBeat::max_try_num_;
}

void HeartBeat::setAlive(bool alive) {
    is_alive_ = alive;
    if (alive) {
        die_count_ = 0;
    } else {
        ++die_count_;
    }
}

bool HeartBeat::isAlive() const {
    return is_alive_;
}

int8_t HeartBeat::dieCount() const {
    return die_count_;
}

void HeartBeat::setMaxTryNum(int8_t max_num) {
    HeartBeat::max_try_num_ = max_num;
}

int8_t HeartBeat::getMaxTryNum() const {
    return HeartBeat::max_try_num_;
}

}