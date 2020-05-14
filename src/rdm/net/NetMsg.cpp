#include "NetMsg.h"
#include "../message/Codec.h"

namespace rdm {

NetMsg::NetMsg() :
        mBuf(nullptr),
        mSocket(nullptr),
        mResolveType(MessageResolveType::BY_PROTOBUF_NAME) {

}

NetMsg::~NetMsg() {

}

void NetMsg::bind(const std::string* str, tcp::socket* socket) {
    mBuf = str;
    mSocket = socket;
}

void NetMsg::bind(const std::string* str, tcp::socket* socket, MessageResolveType type) {
    mBuf = str;
    mSocket = socket;
    mResolveType = type;
}

const std::string* NetMsg::getBuf() {
    return mBuf;
}

google::protobuf::Message* NetMsg::getProtoMsg() const {
    return decode(*mBuf);
}

tcp::socket* NetMsg::getSocket() const {
    return mSocket;
}

MessageResolveType NetMsg::getResolveType() const {
    return mResolveType;
}

}