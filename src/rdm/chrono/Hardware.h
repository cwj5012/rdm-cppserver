#pragma once

#include <cstdint>

namespace rdm {

inline uint64_t hardware_timestamp() {
#ifdef __linux__
    return __builtin_ia32_rdtsc();
#else
    return 0; // todo
#endif
}

}