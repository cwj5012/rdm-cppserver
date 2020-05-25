#pragma once

#include <memory>

namespace rdm {

class NetServer;
class Command;
class DBServiceManager;
class NetClientManager;
class NetConnectionManager;
class TimerManager;
class ThreadPool;

class Service {
public:
    Service();
    virtual ~Service();

    virtual bool onInit() = 0;
    virtual void onRun() = 0;
    virtual bool onExit() = 0;

    bool init();
    void run();
    void exit();

private:
    std::shared_ptr<NetServer> net_server_;
    std::shared_ptr<Command> command_;
    std::shared_ptr<DBServiceManager> db_manager_;
    std::shared_ptr<NetClientManager> client_manager_;
    std::shared_ptr<TimerManager> timer_manager_;
    std::shared_ptr<ThreadPool> thread_pool_;
    std::shared_ptr<NetConnectionManager> connection_manager_;
};

}

