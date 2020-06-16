#include "NetMsg.h"
#include "../message/Codec.h"

namespace rdm {

NetMsg::NetMsg() :
        buf_(nullptr),
        mSocket(nullptr),
        resolver_type_(MessageResolveType::kByProtobufEnum) {

}

NetMsg::~NetMsg() {

}

void NetMsg::bind(const std::string* str, tcp::socket* socket) {
    buf_ = str;
    mSocket = socket;
}

void NetMsg::bind(const std::string* str, tcp::socket* socket, MessageResolveType type) {
    buf_ = str;
    mSocket = socket;
    resolver_type_ = type;
}

const std::string* NetMsg::getBuf() const {
    return buf_;
}

google::protobuf::Message* NetMsg::getProtoMsg() const {
    return decodeE(*buf_);
}

tcp::socket* NetMsg::getSocket() const {
    return mSocket;
}

MessageResolveType NetMsg::getResolveType() const {
    return resolver_type_;
}

}