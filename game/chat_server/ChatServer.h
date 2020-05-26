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

    void newChatRoom(const std::string& arg);

private:
    uint64_t room_id_{0};
    std::map<uint64_t, ChatRoom::uptr> chat_rooms_;
};


