#include "Service.h"

#include <memory>

#include "../database/mysql/DBServiceManager.h"
#include "../net/NetServer.h"
#include "../net/NetClientManager.h"
#include "../net/NetManager.h"
#include "../thread/ThreadPool.h"
#include "../timer/TimerManager.h"
#include "../log/Logger.h"
#include "../command/Command.h"
#include "../Version.h"

namespace rdm {

Service::Service() {
    LOG_INFO("================================================");
    LOG_INFO("service start...");
    LOG_INFO("{} {}", "version:", kRdmVersion);
    LOG_INFO("================================================");

    net_server_ = std::make_shared<NetServer>();
    if (!net_server_) {
        LOG_ERROR("net server create error.");
    }

    auto& net_manager = NetManager::inst();

    thread_pool_ = std::make_shared<ThreadPool>(&net_manager.getService(), 4);
    if (!thread_pool_) {
        LOG_ERROR("thread pool create error.");
    }

    command_ = std::make_shared<Command>();
    if (!command_) {
        LOG_ERROR("command create error.");
    }


    db_manager_ = std::make_shared<DBServiceManager>();
    if (!db_manager_) {
        LOG_ERROR("database manager create error.");
    }

    timer_manager_ = std::make_shared<TimerManager>(&net_manager.getService());
    if (!timer_manager_) {
        LOG_ERROR("timer manager create error.");
    }

    client_manager_ = std::make_shared<NetClientManager>();
    if (!client_manager_) {
        LOG_ERROR("client manager create error.");
    }

    LOG_INFO("all component create success.");
}

Service::~Service() {

}

bool Service::init() {
    net_server_->init();
    client_manager_->init();
    command_->init();
    db_manager_->init();

    onInit();

    return false;
}

void Service::run() {
    LOG_INFO("service is running...");

    command_->run();
    net_server_->run(); // boost asio 阻塞
}

void Service::exit() {

}

}