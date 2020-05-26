#include "DBServiceManager.h"
#include "DBConnectionPool.h"
#include "IDBConnection.h"
#include "../../log/Logger.h"

namespace rdm {

DBServiceManager::DBServiceManager()
        : thread_num_(1) {

    DatabaseLoginInfo info;
    info.name = "root";
    info.passwd = "1234";
    info.ip = "127.0.0.1";
    info.port = 3306;

    mDBConnectionPool = new DBConnectionPool(info);

    LOG_INFO("mysql connection pool create success.");
    LOG_INFO("mysql info {}:{}.", info.ip, info.port);
}

DBServiceManager::~DBServiceManager() {

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

    for (auto i = 0; i < thread_num_; ++i) {
        DatabaseLoginInfo info;
//            DBConnection db_service(info);
//            db_service.connect();
//
//            db_service_.push_back(&db_service);
    }
}

}