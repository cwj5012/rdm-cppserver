#pragma once

#include <memory>

#include <rdm/service/Service.h>

#include "ChatRoom.h"

class MasterServer : public rdm::Service {
public:
    MasterServer();
    ~MasterServer() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    uint64_t room_id_{0};
    std::map<uint64_t, ChatRoom::uptr> chat_rooms_;
};


