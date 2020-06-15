#pragma once

#include <memory>

#include <rdm/service/Service.h>
#include <rdm/command/Options.h>

class Client : public rdm::Service {
public:
    Client();
    ~Client() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:
    rdm::Options op_;
};


