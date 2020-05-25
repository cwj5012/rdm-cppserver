#pragma once

#include <rdm/service/Service.h>

#include "ChatRoom.h"

class ChatServer : public rdm::Service {
public:
    ChatServer();
    ~ChatServer() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    ChatRoom* chat_room_;
};


