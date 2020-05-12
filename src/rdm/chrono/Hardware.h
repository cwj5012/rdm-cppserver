#pragma once

#include <cstdint>

namespace rdm {

inline uint64_t hardware_timestamp() {
    return __builtin_ia32_rdtsc();
}

}