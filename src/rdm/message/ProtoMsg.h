#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include <google/protobuf/message.h>

#include "../log/Logger.h"

namespace rdm {

const uint16_t HEADER_SIZE = 4;

struct MsgHead {
    uint16_t usSize;
    uint16_t usType;

    MsgHead() : usType(0), usSize(0) {}

    MsgHead(uint16_t type, uint16_t size) : usType(type), usSize(size) {}
};

template<typename T>
class ProtoMsg {
public:
    typedef std::shared_ptr<T> MessagePointer;
    typedef std::vector<uint8_t> DataBuffer;

    ProtoMsg() = delete;

    explicit ProtoMsg(MessagePointer msg)
            : message_(msg) {}

    ~ProtoMsg() = default;

    MessagePointer getMsg() const {
        return message_;
    }

    bool packData(DataBuffer& buf) {
        if (!message_)
            return false;

        unsigned msg_size = message_->ByteSize();
        buf.resize(HEADER_SIZE + msg_size);
        encodeHeader(buf, msg_size);
        return message_->SerializeToArray(&buf[HEADER_SIZE], msg_size);
    }

    bool getData(const DataBuffer& buf) {
        return message_->ParseFromArray(&buf[HEADER_SIZE], static_cast<int>(buf.size() - HEADER_SIZE));
    }

private:

    // 消息长度存在消息头 4 字节
    bool encodeHeader(DataBuffer& buf, uint16_t size) {
        if (buf.size() < HEADER_SIZE) {
            LOG_ERROR("encode header error, buf size: {}", buf.size());
            return false;
        }

        buf[0] = static_cast<uint8_t>((size >> 24) & 0xFF);
        buf[1] = static_cast<uint8_t>((size >> 16) & 0xFF);
        buf[2] = static_cast<uint8_t>((size >> 8) & 0xFF);
        buf[3] = static_cast<uint8_t>(size & 0xFF);
        return true;
    }

    // 读取消息头 4 字节，获取消息长度
    uint16_t decodeHeader(const DataBuffer& buf) {
        if (buf.size() < HEADER_SIZE) {
            return 0;
        }
        uint16_t msg_size = 0;
        for (uint16_t i = 0; i < HEADER_SIZE; ++i) {
            // 2 ^ 8 = 256
            msg_size = static_cast<uint16_t>(msg_size * 256 + (buf[i]) & 0xFF);
        }
        return msg_size;
    }

    DataBuffer buf_;
    MessagePointer message_;
};

}