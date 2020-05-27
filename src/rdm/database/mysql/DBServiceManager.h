﻿#pragma once

#include <vector>
#include <cstdint>

#include "DBConnection.h"
#include "DBConnectionPool.h"

namespace rdm {

class Service;

class DBServiceManager {
public:
    explicit DBServiceManager();
    explicit DBServiceManager(const std::shared_ptr<Service>& service);

    ~DBServiceManager();

    DBServiceManager& inst();

    void setThreadNum(int32_t num);

    int32_t getThreadNum() const;

    DBConnectionPool* getDBConnectionPool();

    void init();

private:
    int32_t thread_num_{1};
    std::vector<DBConnection*> db_connections_;

    DBConnectionPool* mDBConnectionPool{nullptr};

    std::weak_ptr<Service> service_;
    DatabaseLoginInfo db_info_{};
};

}



