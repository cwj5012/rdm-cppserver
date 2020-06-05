#pragma once

#include <cstdint>

enum class MessageType : uint32_t {
    kNone = 0,

    kCommand = 1001,

    kLogin = 2001,
};