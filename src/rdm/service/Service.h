#pragma once

#include <memory>
#include <string>

namespace rdm {

class NetServer;
class Command;
class DBServiceManager;
class NetClientManager;
class NetConnectionManager;
class TimerManager;
class ThreadPool;
class ServerNetConfig;

class Service : public std::enable_shared_from_this<Service> {
public:
    Service();
    virtual ~Service();

    virtual bool onInit() = 0;
    virtual void onRun() = 0;
    virtual bool onExit() = 0;

    bool init();
    void run();
    void exit();

    void setConfigPath(std::string&& path);
    void setConfigKey(std::string&& key);

    [[nodiscard]] const std::shared_ptr<NetServer>& getNetServer() const;
    [[nodiscard]] const std::shared_ptr<Command>& getCommand() const;
    [[nodiscard]] const std::shared_ptr<DBServiceManager>& getDbManager() const;
    [[nodiscard]] const std::shared_ptr<NetClientManager>& getClientManager() const;
    [[nodiscard]] const std::shared_ptr<TimerManager>& getTimerManager() const;
    [[nodiscard]] const std::shared_ptr<ThreadPool>& getThreadPool() const;
    [[nodiscard]] const std::shared_ptr<NetConnectionManager>& getConnectionManager() const;
    [[nodiscard]] const std::shared_ptr<ServerNetConfig>& getServerNetConfig() const;

private:
    enum Status {
        none,
        init_ok,
        init_error,
    };
    Status status_{init_error};
    std::shared_ptr<NetServer> net_server_;
    std::shared_ptr<Command> command_;
    std::shared_ptr<DBServiceManager> db_manager_;
    std::shared_ptr<NetClientManager> client_manager_;
    std::shared_ptr<TimerManager> timer_manager_;
    std::shared_ptr<ThreadPool> thread_pool_;
    std::shared_ptr<NetConnectionManager> net_connection_manager_;
    std::shared_ptr<ServerNetConfig> server_net_config_;
};

}

