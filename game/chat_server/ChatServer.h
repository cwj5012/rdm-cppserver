#pragma once

#include <memory>

#include <rdm/service/Service.h>

#include "ChatRoom.h"

/**
 * 聊天室服务器
 * 支持创建聊天室，进入聊天室
 * 收发消息
 */
class ChatServer : public rdm::Service {
public:
    ChatServer();
    ~ChatServer() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    std::map<uint32_t, ChatRoom::uptr> chat_rooms_;
};


