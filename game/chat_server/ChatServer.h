#pragma once

#include <memory>

#include <rdm/service/Service.h>

#include "ChatRoom.h"
#include "WebCommand.h"

/**
 * 聊天室服务器
 * 支持创建聊天室，进入聊天室
 * 收发消息
 */
class ChatServer
        : public rdm::Service {
public:
    ChatServer();
    ~ChatServer() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    uint64_t room_id_{0};
    std::map<uint64_t, ChatRoom::uptr> chat_rooms_;
    WebCommand::uptr web_command_;

};


