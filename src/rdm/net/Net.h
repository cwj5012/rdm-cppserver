#pragma once

#include <string>

namespace rdm {

class Addr {
public:
    Addr(int socketType, const std::string& host, uint16_t port);
    [[nodiscard]] std::string network() const;
    [[nodiscard]] std::string str() const;

private:
    std::string network_;
    std::string str_;
};

}