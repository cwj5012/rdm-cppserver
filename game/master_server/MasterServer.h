#pragma once

#include <memory>

#include <rdm/service/Service.h>

class MasterServer : public rdm::Service {
public:
    MasterServer();
    ~MasterServer() override;

    bool onInit() override;
    void onRun() override;
    bool onExit() override;

private:

};


