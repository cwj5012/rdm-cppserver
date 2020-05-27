﻿#include "DBServiceManager.h"
#include "DBConnectionPool.h"
#include "IDBConnection.h"
#include "../../log/Logger.h"
#include "../../service/Service.h"
#include "../../config/ServerNetConfig.h"

namespace rdm {

DBServiceManager::DBServiceManager() {
    if (mDBConnectionPool == nullptr) {
        // todo 默认登录信息，等没用了删除
        db_info_.name = "root";
        db_info_.passwd = "1234";
        db_info_.ip = "127.0.0.1";
        db_info_.port = 3306;

        mDBConnectionPool = new DBConnectionPool(db_info_);
    }
}

DBServiceManager::DBServiceManager(const std::shared_ptr<Service>& service)
        : service_(service) {
    if (mDBConnectionPool == nullptr) {
        auto info = service_.lock()->getServerNetConfig()->getServerNetInfo();

        db_info_.name = info->mysql_info.user_name;
        db_info_.passwd = info->mysql_info.password;
        db_info_.ip = info->mysql_info.host;
        db_info_.port = std::stoi(info->mysql_info.port);

        mDBConnectionPool = new DBConnectionPool(db_info_);
    }
}

DBServiceManager::~DBServiceManager() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

DBServiceManager& DBServiceManager::inst() {
    static DBServiceManager obj;
    return obj;
}

void DBServiceManager::setThreadNum(int32_t num) {
    thread_num_ = num;
}

int32_t DBServiceManager::getThreadNum() const {
    return thread_num_;
}

DBConnectionPool* DBServiceManager::getDBConnectionPool() {
    return mDBConnectionPool;
}

void DBServiceManager::init() {
    LOG_INFO("DBServiceManager::init");

    mDBConnectionPool->initPool(4);

    LOG_INFO("mysql connection pool num: 4, create success, {}:{}.", db_info_.ip, db_info_.port);

    for (auto i = 0; i < thread_num_; ++i) {
        DatabaseLoginInfo info;
//            DBConnection db_service(info);
//            db_service.connect();
//
//            db_connections_.push_back(&db_service);
    }
}

}