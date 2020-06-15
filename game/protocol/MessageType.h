#pragma once

#include <cstdint>

enum class MessageType : uint32_t {
    kNone = 0,

    kCommand = 1001,
    kEcho = 1002,
    kAuth = 1003,

    kLogin = 2001,
};