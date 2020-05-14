#pragma once

#include <cstdint>
#include <cassert>

namespace rdm {

/**
 * 稀疏数组
 */
class SparseByteSet {
public:
    static constexpr uint16_t kCapacity = 256;

    SparseByteSet() : size_(0) {}

    inline bool add(uint8_t i) {
        bool r = !contains(i);
        if (r) {
            assert(size_ < kCapacity);
            dense_[size_] = i;
            sparse_[i] = static_cast<uint8_t>(size_);
            ++size_;
        }
        return r;
    }

    inline bool contains(uint8_t i) const {
        return sparse_[i] < size_ && dense_[sparse_[i]] == i;
    }

private:
    uint16_t size_;
    uint8_t sparse_[kCapacity];
    uint8_t dense_[kCapacity];
};

} // namespace rdm