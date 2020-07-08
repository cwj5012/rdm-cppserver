#include "Net.h"

#ifdef __linux__
#include <sys/types.h>
#else
#include <Windows.h>
#endif

namespace rdm {

Addr::Addr(int socketType, const std::string& host, uint16_t port) {
    switch (socketType) {
        case SOCK_STREAM:
            network_ = "tcp";
            break;
        case SOCK_DGRAM:
            network_ = "udp";
            break;
        default:
            break;
    }
    str_ = host + ":" + std::to_string(port);
}

std::string Addr::network() const {
    return network_;
}

std::string Addr::str() const {
    return str_;
}

}