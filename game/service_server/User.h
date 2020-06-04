#pragma once

#include <cstdint>
#include <string>

class User {
public:
    User();
    ~User();

private:
    uint64_t id_{0};
    std::string name_;
};


