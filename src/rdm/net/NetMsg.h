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
    BY_PROTOBUF_NAME = 0,   // 根据 protobuf 消息名字
    BY_PROTOBUF_TYPE = 1    // 根据 protobuf 附加的枚举
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
    const std::string* mBuf;
    tcp::socket* mSocket;
    MessageResolveType mResolveType;
};

}