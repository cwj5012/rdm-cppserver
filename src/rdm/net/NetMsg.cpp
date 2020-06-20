#include "NetMsg.h"
#include "../message/Codec.h"

namespace rdm {

NetMsg::NetMsg() :
        buf_(nullptr),
        socket_(nullptr),
        resolver_type_(MessageResolveType::kByProtobufEnum) {

}

NetMsg::~NetMsg() {

}

void NetMsg::bind(const std::string* str, tcp::socket* socket) {
    buf_ = str;
    socket_ = socket;
}

void NetMsg::bind(const std::string* str, tcp::socket* socket, MessageResolveType type) {
    buf_ = str;
    socket_ = socket;
    resolver_type_ = type;
}

const std::string* NetMsg::getBuf() const {
    return buf_;
}

google::protobuf::Message* NetMsg::getProtoMsg() const {
    return decodeE(*buf_);
}

tcp::socket* NetMsg::getSocket() const {
    return socket_;
}

MessageResolveType NetMsg::getResolveType() const {
    return resolver_type_;
}

}