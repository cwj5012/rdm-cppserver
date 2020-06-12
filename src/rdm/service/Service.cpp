#include "Service.h"

#include <memory>

#include "../database/mysql/DBServiceManager.h"
#include "../net/NetServer.h"
#include "../net/NetConnectionManager.h"
#include "../net/NetClientManager.h"
#include "../net/NetManager.h"
#include "../config/ServerNetConfig.h"
#include "../thread/ThreadPool.h"
#include "../timer/TimerManager.h"
#include "../log/Logger.h"
#include "../command/Command.h"
#include "../Version.h"
#include "../thread/ThreadUtil.h"

namespace rdm {

Service::Service() {
    // msvc 不支持
    // LOG_INFO("pid: {}, tid: {}.", getpid(), gettid());

    server_net_config_ = std::make_shared<ServerNetConfig>();
    if (server_net_config_ == nullptr) {
        LOG_ERROR("server net config create error.");
    }
}

Service::~Service() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

bool Service::init() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    LOG_INFO("================================================");
    LOG_INFO("service start...");
    LOG_INFO("{} {}", "version:", kRdmVersion);
    LOG_INFO("================================================");

    if (!server_net_config_->init()) {
        LOG_ERROR("server net config init error.");
    }

    net_server_ = std::make_shared<NetServer>(shared_from_this());
    if (!net_server_) {
        LOG_ERROR("net server create error.");
    }

    auto& net_manager = NetManager::inst();

    thread_pool_ = std::make_shared<ThreadPool>(&net_manager.getService(), 4);
    if (!thread_pool_) {
        LOG_ERROR("thread pool create error.");
    }

    command_ = std::make_shared<Command>(shared_from_this());
    if (!command_) {
        LOG_ERROR("command create error.");
    }

    db_manager_ = std::make_shared<DBServiceManager>(shared_from_this());
    if (!db_manager_ || db_manager_->status() != 0) {
        LOG_ERROR("database manager create error.");
    }

    timer_manager_ = std::make_shared<TimerManager>(&net_manager.getService());
    if (!timer_manager_) {
        LOG_ERROR("timer manager create error.");
    }

    client_manager_ = std::make_shared<NetClientManager>(shared_from_this());
    if (!client_manager_) {
        LOG_ERROR("client manager create error.");
    }

    net_connection_manager_ = std::make_shared<NetConnectionManager>();
    if (!net_connection_manager_) {
        LOG_ERROR("net connection manager create error.");
    }

    LOG_INFO("all components create success.");

    net_server_->init();
    client_manager_->init();
    command_->init();
    db_manager_->init();

    while (true) {
        ThreadUtil::sleep(1000);

        // todo 异步加载的模块，要检查状态
        LOG_INFO("all components init success.");

        break;
    }

    onInit();

    return true;
}

void Service::run() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    command_->run();
    net_server_->run(); // boost asio 阻塞
}

void Service::exit() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);

    net_connection_manager_->release();

    net_server_->release();
    command_->release();
    // db_manager_->release();
    // client_manager_->release();
    // timer_manager_->release();
    // thread_pool_->release();
}

const std::shared_ptr<NetServer>& Service::getNetServer() const {
    return net_server_;
}

const std::shared_ptr<Command>& Service::getCommand() const {
    return command_;
}

const std::shared_ptr<DBServiceManager>& Service::getDbManager() const {
    return db_manager_;
}

const std::shared_ptr<NetClientManager>& Service::getClientManager() const {
    return client_manager_;
}

const std::shared_ptr<TimerManager>& Service::getTimerManager() const {
    return timer_manager_;
}

const std::shared_ptr<ThreadPool>& Service::getThreadPool() const {
    return thread_pool_;
}

const std::shared_ptr<NetConnectionManager>& Service::getConnectionManager() const {
    return net_connection_manager_;
}

const std::shared_ptr<ServerNetConfig>& Service::getServerNetConfig() const {
    return server_net_config_;
}

void Service::setConfigPath(std::string&& path) {
    server_net_config_->setPath(path);
}

}