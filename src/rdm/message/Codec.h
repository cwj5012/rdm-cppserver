/*
 * encode, decode 基于 protobuf 消息名称解析
 * message struct
 *      message length           32bit 消息长度，不包括头部的 32bit
 *      message name length      32bit
 *      message name
 *      message contenxt
 *
 * encodeE, decodeE 基于 protobuf 消息枚举解析，每个消息需要做个唯一枚举值
 * message struct
 *      message length           32bit 消息长度，不包括头部的 32bit
 *      message enum value       32bit
 *      message contenxt
 *
 * encodeM, decodeM 基于 protobuf 消息名称解析，包含多条 protobuf 消息
 * message struct
 *      message length           32bit 消息长度，不包括头部的 32bit
 *      message number           32bit 包含的消息个数（待定，暂时不加这个字段）
 *      message name length      32bit 消息(1)
 *      message name
 *      message contenxt length  32bit
 *      message contenxt
 *      message name length      32bit 消息(2)
 *      message name
 *      message contenxt length  32bit
 *      message contenxt
 *      ...
 *
 */

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <stdint.h>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "../log/Logger.h"

using google::protobuf::Descriptor;
using google::protobuf::DescriptorPool;
using google::protobuf::Message;
using google::protobuf::MessageFactory;
using google::protobuf::Reflection;
using google::protobuf::FieldDescriptor;

const int kHeaderLen = sizeof(int32_t); // 一般等于 4
const int kHeaderLenX2 = kHeaderLen * 2;
const int kMaxMessageNum = 10;              // 一条消息中包含的子消息数量上限

namespace rdm {

/**
 * protobuf::Message 对象编码为字符串（基于消息名称）
 * @param message
 * @return
 */
inline static std::string encode(const google::protobuf::Message& message);

/**
 * 字符串解析为 protobuf::Message 对象（基于消息名称）
 * @param buf
 * @return
 */
inline google::protobuf::Message* decode(const std::string& buf);

/**
 * protobuf::Message 对象编码为字符串（基于消息枚举）
 * @param message
 * @return
 */
inline static std::string encodeE(const google::protobuf::Message& message);

/**
 * 字符串解析为 protobuf::Message 对象（基于消息枚举）
 * @param buf
 * @return
 */
inline static google::protobuf::Message* decodeE(const std::string& buf);

/**
 * 编码单条消息，不包含消息头
 *
 * message struct
 *      message name length      32bit
 *      message name
 *      message context length   32bit
 *      message context
 *
 * @param message
 * @return
 */
inline static std::string encodeS(const google::protobuf::Message& message);

/**
 * 编码多条消息，不包含消息头
 *
 * message struct
 *      message name length      32bit 消息 1
 *      message name
 *      message context length   32bit
 *      message context
 *      message name length      32bit 消息 2
 *      message name
 *      message context length   32bit
 *      message context
 *      ...                             消息 N
 *
 * @param messages
 * @return
 */
inline static std::string encodeM(const std::vector<const google::protobuf::Message*> messages);

/**
 * 编码多条消息，包含消息头
 *
 * message struct
 *      message length           32bit 消息长度，不包括头部的 32bit
 *      message name length      32bit 消息 1
 *      message name
 *      message context length   32bit
 *      message context
 *      message name length      32bit 消息 2
 *      message name
 *      message context length   32bit
 *      message context
 *      ...                             消息 N
 *
 * @param messages
 * @return
 */
inline static std::string encodeMH(const std::vector<const google::protobuf::Message*> messages);

/**
 * 解析包含单条消息的协议
 *
 * message struct
 *      message name length      32bit
 *      message name
 *      message context length   32bit
 *      message context
 *
 * @param buf
 * @param end_buf 解析完单条消息后，末尾其余的字符串
 * @return
 */
inline static google::protobuf::Message* decodeS(const std::string& buf, std::string& end_buf);

/**
 * 解析包含多条消息的协议
 *
 * message struct
 *      message name length      32bit 消息 1
 *      message name
 *      message context length   32bit
 *      message context
 *      message name length      32bit 消息 2
 *      message name
 *      message context length   32bit
 *      message context
 *      ...                             消息 N
 *
 * @param buf
 * @return
 */
inline static std::vector<google::protobuf::Message*> decodeM(const std::string& buf);

/**
 * 获取包含头部的消息
 * @param buf
 * @return
 */
inline static std::string packHeader(const std::string& buf);

/**
 * 获取去掉头部的消息
 * @param buf
 * @return
 */
inline static std::string unpackHeader(const std::string& buf);

inline uint32_t byte4ToInt32(char* buf) {
    return uint32_t((uint8_t) (buf[0]) << 24u |
                    (uint8_t) (buf[1]) << 16u |
                    (uint8_t) (buf[2]) << 8u |
                    (uint8_t) (buf[3]));
}

inline uint32_t byte4ToInt32(const std::string& buf) {
    if (buf.size() < 4) return 0;
    return uint32_t((uint8_t) (buf[0]) << 24u |
                    (uint8_t) (buf[1]) << 16u |
                    (uint8_t) (buf[2]) << 8u |
                    (uint8_t) (buf[3]));
}

inline uint32_t byte4ToInt32Big(char* buf) {
    return uint32_t((uint8_t) (buf[3]) << 24u |
                    (uint8_t) (buf[2]) << 16u |
                    (uint8_t) (buf[1]) << 8u |
                    (uint8_t) (buf[0]));
}

/*********************************
 *
 * definition
 *
 *********************************/

std::string encode(const google::protobuf::Message& message) {
    std::string result;

    result.resize(kHeaderLen);

    // 消息名长度
    const std::string& type_name = message.GetTypeName();
    int32_t name_len = static_cast<int32_t>(type_name.size() + 1 - 1); // 转为 char* 末尾是 /0 所以长度加一

    char buf[4];
    buf[0] = static_cast<uint8_t>((name_len >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((name_len >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((name_len >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(name_len & 0xFF);
    result.append(buf, kHeaderLen);

    // 消息名
    result.append(type_name.c_str(), name_len);

    // 消息内容
    bool succeed = message.AppendToString(&result);

    if (succeed) {
        // 消息长度
        int32_t len = static_cast<int32_t>(result.size()) - kHeaderLen;

        char buf_len[4];
        buf_len[0] = static_cast<uint8_t>((len >> 24) & 0xFF);
        buf_len[1] = static_cast<uint8_t>((len >> 16) & 0xFF);
        buf_len[2] = static_cast<uint8_t>((len >> 8) & 0xFF);
        buf_len[3] = static_cast<uint8_t>(len & 0xFF);

        std::copy(buf_len,
                  buf_len + sizeof(buf_len),
                  result.begin());
    } else {
        result.clear();
    }

    return result;
}

google::protobuf::Message* decode(const std::string& buf) {
    google::protobuf::Message* result = nullptr;

    int32_t len = static_cast<int32_t>(buf.length());

    if (len >= kHeaderLenX2) {
        const char* begin = buf.c_str() + kHeaderLen;

        int32_t name_len = 0;
        name_len += (uint8_t) begin[0] << 24;
        name_len += (uint8_t) begin[1] << 16;
        name_len += (uint8_t) begin[2] << 8;
        name_len += (uint8_t) begin[3];

        if (name_len >= 2 && name_len <= len - kHeaderLenX2) {
            std::string type_name(buf.begin() + kHeaderLenX2,
                                  buf.begin() + kHeaderLenX2 + name_len); // name_len - 1

            const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
            if (desc == nullptr) {
                LOG_ERROR("FindMessageTypeByName failed, type name: {}", type_name);
                return result;
            }
            const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
            if (proto == nullptr) {
                LOG_ERROR("GetPrototype failed, type name: {}", type_name);
                return result;
            }

            Message* message = proto->New();

            if (message) {
                const char* data = buf.c_str() + kHeaderLenX2 + name_len;
                int32_t dataLen = len - name_len - kHeaderLenX2;
                if (message->ParseFromArray(data, dataLen)) {
                    result = message;
                } else {
                    // 解析错误
                    LOG_ERROR("ParseFromArray failed, len: {}", dataLen);
                    delete message;
                }
            } else {
                LOG_ERROR("proto->New() failed");
                // 消息创建失败，为空指针
            }
        } else {
            LOG_ERROR("length is not enough");
            // 消息总长度不足
        }
    }

    return result;
}

std::string encodeE(const google::protobuf::Message& message) {
    std::string result;

    result.resize(kHeaderLen);

    // 消息枚举
    // todo 写死枚举编号测试
    int32_t message_enum = 99;

    char buf[4];
    buf[0] = static_cast<uint8_t>((message_enum >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((message_enum >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((message_enum >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(message_enum & 0xFF);
    result.append(buf, kHeaderLen);

    // 消息内容
    bool succeed = message.AppendToString(&result);

    if (succeed) {
        // 消息长度
        int32_t len = static_cast<int32_t>(result.size()) - kHeaderLen;

        char buf_len[4];
        buf_len[0] = static_cast<uint8_t>((len >> 24) & 0xFF);
        buf_len[1] = static_cast<uint8_t>((len >> 16) & 0xFF);
        buf_len[2] = static_cast<uint8_t>((len >> 8) & 0xFF);
        buf_len[3] = static_cast<uint8_t>(len & 0xFF);

        std::copy(buf_len,
                  buf_len + sizeof(buf_len),
                  result.begin());
    } else {
        result.clear();
    }

    return result;
}

google::protobuf::Message* decodeE(const std::string& buf) {
    google::protobuf::Message* result = nullptr;

    int32_t len = static_cast<int32_t>(buf.length());

    if (len >= kHeaderLen) {
        const char* begin = buf.c_str();

        int32_t message_enum = 0;
        message_enum += (uint8_t) begin[0] << 24;
        message_enum += (uint8_t) begin[1] << 16;
        message_enum += (uint8_t) begin[2] << 8;
        message_enum += (uint8_t) begin[3];

        if (message_enum >= 0) {
            std::string type_name("Person");

            const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
            if (desc == nullptr) {
                LOG_ERROR("FindMessageTypeByName failed, type name: {}", type_name);
                return result;
            }
            const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
            if (proto == nullptr) {
                LOG_ERROR("GetPrototype failed, type name: {}", type_name);
                return result;
            }

            Message* message = proto->New();

            if (message) {
                const char* data = buf.c_str() + kHeaderLen;
                int32_t dataLen = len - kHeaderLen;
                if (message->ParseFromArray(data, dataLen)) {
                    result = message;
                } else {
                    // 解析错误
                    delete message;
                }
            } else {
                // 消息创建失败，为空指针
            }
        } else {
            // 消息枚举小于零
        }
    }

    return result;
}

std::string encodeS(const google::protobuf::Message& message) {
    std::string result;

    const std::string& type_name = message.GetTypeName();
    int32_t name_len = static_cast<int32_t>(type_name.size() + 1 - 1); // 转为 char* 末尾是 /0 所以长度加一

    char buf[4];
    buf[0] = static_cast<uint8_t>((name_len >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((name_len >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((name_len >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(name_len & 0xFF);
    result.append(buf, kHeaderLen);

    // 消息名
    result.append(type_name.c_str(), name_len);

    std::string context;
    bool succeed = message.SerializeToString(&context);

    if (!succeed) {
        return "";
    }

    int32_t context_len = static_cast<int32_t>(context.size());
    buf[0] = static_cast<uint8_t>((context_len >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((context_len >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((context_len >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(context_len & 0xFF);

    // 消息内容长度
    result.append(buf, kHeaderLen);

    // 消息内容
    result.append(context);

    return result;
}

std::string encodeM(const std::vector<const google::protobuf::Message*> messages) {
    std::string result;

    for (int i = 0; i < messages.size(); ++i) {
        result.append(encodeS(*messages[i]));
    }

    return result;
}

google::protobuf::Message* decodeS(const std::string& buf, std::string& end_buf) {
    google::protobuf::Message* result = nullptr;

    int32_t len = static_cast<int32_t>(buf.length());

    if (len >= kHeaderLen) {
        const char* begin = buf.c_str();

        int32_t name_len = 0;
        name_len += (uint8_t) begin[0] << 24;
        name_len += (uint8_t) begin[1] << 16;
        name_len += (uint8_t) begin[2] << 8;
        name_len += (uint8_t) begin[3];

        int32_t context_len = 0;
        context_len += (uint8_t) begin[name_len + 4] << 24;
        context_len += (uint8_t) begin[name_len + 5] << 16;
        context_len += (uint8_t) begin[name_len + 6] << 8;
        context_len += (uint8_t) begin[name_len + 7];

        if (name_len >= 2 && name_len <= len - kHeaderLen) {
            std::string type_name(buf.begin() + kHeaderLen, buf.begin() + kHeaderLen + name_len); // name_len - 1

            const Descriptor* desc = DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
            if (desc == nullptr) {
                LOG_ERROR("FindMessageTypeByName failed, type name: {}", type_name);
                return result;
            }
            const Message* proto = MessageFactory::generated_factory()->GetPrototype(desc);
            if (proto == nullptr) {
                LOG_ERROR("GetPrototype failed, type name: {}", type_name);
                return result;
            }

            Message* message = proto->New();

            if (message) {
                const char* data = buf.c_str() + kHeaderLen + name_len + kHeaderLen;
                int32_t dataLen = len - name_len - kHeaderLen;
                if (message->ParseFromArray(data, context_len)) {
                    result = message;

                    // 截取末尾剩余的字符串
                    int32_t end_pos = kHeaderLenX2 + name_len + context_len;
                    if (buf.length() >= end_pos) {
                        end_buf = buf.substr(end_pos);
                    }

                } else {
                    // 解析错误
                    LOG_ERROR("ParseFromArray failed, len: {}, type name: {}", dataLen, type_name);
                    delete message;
                }
            } else {
                LOG_ERROR("proto->New() failed, type name: {}", type_name);
                // 消息创建失败，为空指针
            }
        } else {
            LOG_ERROR("name length {} is not enough", len);
            // 消息总长度不足
        }
    }
    return result;
}

std::vector<google::protobuf::Message*> decodeM(const std::string& buf) {
    std::vector<google::protobuf::Message*> results;

    int32_t len = static_cast<int32_t>(buf.length());

    if (len >= kHeaderLen) {
        std::string msg_buf = buf;
        std::string end_buf;
        for (int i = 0; i < kMaxMessageNum; ++i) {
            auto result = decodeS(msg_buf, end_buf);
            msg_buf = end_buf;
            if (result != nullptr) {
                results.push_back(result);
            } else {
                break;
            }
        }
    }

    return results;
}

std::string encodeMH(const std::vector<const google::protobuf::Message*> messages) {
    std::string result;

    result.resize(kHeaderLen);

    result.append(encodeM(messages));

    // 消息长度
    int32_t len = static_cast<int32_t>(result.size()) - kHeaderLen;

    char buf_len[4];
    buf_len[0] = static_cast<uint8_t>((len >> 24) & 0xFF);
    buf_len[1] = static_cast<uint8_t>((len >> 16) & 0xFF);
    buf_len[2] = static_cast<uint8_t>((len >> 8) & 0xFF);
    buf_len[3] = static_cast<uint8_t>(len & 0xFF);

    std::copy(buf_len,
              buf_len + sizeof(buf_len),
              result.begin());

    return result;
}

std::string packHeader(const std::string& buf) {
    std::string result;
    auto len = static_cast<int32_t>(buf.length());

    char buf_len[4];
    buf_len[0] = static_cast<uint8_t>((len >> 24) & 0xFF);
    buf_len[1] = static_cast<uint8_t>((len >> 16) & 0xFF);
    buf_len[2] = static_cast<uint8_t>((len >> 8) & 0xFF);
    buf_len[3] = static_cast<uint8_t>(len & 0xFF);

    result.append(buf_len, kHeaderLen);
    result.append(buf);

    return result;
}

std::string unpackHeader(const std::string& buf) {
    std::string result;

    if (buf.length() >= kHeaderLen) {
        result = buf.substr(4, buf.length() - 4);
    }

    return result;
}


} // namespace rdm