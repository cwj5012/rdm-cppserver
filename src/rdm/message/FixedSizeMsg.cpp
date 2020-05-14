#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "FixedSizeMsg.h"

namespace rdm {

const char* FixedSizeMsg::data() const {
    return data_;
}

char* FixedSizeMsg::data() {
    return data_;
}

int32_t FixedSizeMsg::data_length() const {
    return HEADER_LENGTH + MAX_BODY_LENGTH;
}

const char* FixedSizeMsg::body() const {
    return data_ + HEADER_LENGTH;
}

char* FixedSizeMsg::body() {
    return data_ + HEADER_LENGTH;
}

int32_t FixedSizeMsg::body_length() const {
    return body_length_;
}

void FixedSizeMsg::body_length(int32_t new_length) {
    body_length_ = new_length;
    if (body_length_ > MAX_BODY_LENGTH) {
        body_length_ = MAX_BODY_LENGTH;
    }
}

bool FixedSizeMsg::decodeHeader() {
    char header[HEADER_LENGTH + 1] = "";
    std::strncat(header, data_, HEADER_LENGTH);
    body_length_ = std::atoi(header);
    if (body_length_ > MAX_BODY_LENGTH) {
        body_length_ = 0;
        return false;
    }
    return true;
}

void FixedSizeMsg::encodeHeader() {
    char header[HEADER_LENGTH + 1] = "";
    std::sprintf(header, "%4d", static_cast<int32_t>(body_length_));
    std::memcpy(data_, header, HEADER_LENGTH);
}

}

