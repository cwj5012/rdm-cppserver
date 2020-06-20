#pragma once

#include <string>

#include <boost/asio.hpp>
#include <google/protobuf/message.h>

using boost::asio::ip::tcp;

namespace rdm {

/**
 * 消息解析类型
 */
enum class MessageResolveType {
    kByProtobufName = 0,   // 根据 protobuf 消息名字
    kByProtobufEnum = 1    // 根据 protobuf 消息枚举
};

struct NetMsg {
public:
    NetMsg();

    ~NetMsg();

    void bind(const std::string* str, tcp::socket* socket);

    void bind(const std::string* str, tcp::socket* socket, MessageResolveType type);

    const std::string* getBuf() const;

    google::protobuf::Message* getProtoMsg() const;

    tcp::socket* getSocket() const;

    MessageResolveType getResolveType() const;

private:
    const std::string* buf_{nullptr};
    uint32_t conn_{0};
    uint64_t session_{0};
    tcp::socket* socket_;
    MessageResolveType resolver_type_{MessageResolveType::kByProtobufEnum};
};

}