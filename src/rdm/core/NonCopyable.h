#pragma once

namespace rdm {

class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

}