#pragma once

#include <cstdint>

namespace rdm {

class FixedSizeMsg {
public:
    enum {
        HEADER_LENGTH = 4,
        MAX_BODY_LENGTH = 1024
    };

    FixedSizeMsg();

    ~FixedSizeMsg() = default;

    const char* data() const;

    char* data();

    int32_t data_length() const;

    const char* body() const;

    char* body();

    int32_t body_length() const;

    void body_length(int32_t new_length);

    bool decodeHeader();

    void encodeHeader();

private:
    char data_[HEADER_LENGTH + MAX_BODY_LENGTH];
    int32_t body_length_;
};

}
