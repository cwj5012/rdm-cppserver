#pragma once

#include <memory>

#include <rdm/service/Service.h>
#include <rdm/command/Options.h>

#include "ChatRoom.h"
#include "WebCommand.h"

class ApiService : public rdm::Service {
public:
    ApiService();
    ~ApiService() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    uint64_t room_id_{0};
    std::map<uint64_t, ChatRoom::uptr> chat_rooms_;
    WebCommand::uptr web_command_;
    rdm::Options op_;
};


