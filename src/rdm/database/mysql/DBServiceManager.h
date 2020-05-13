#pragma once

#include <vector>
#include <cstdint>

#include "DBConnection.h"
#include "DBConnectionPool.h"

namespace rdm {

class DBServiceManager {
public:
    DBServiceManager();

    ~DBServiceManager();

    DBServiceManager& inst();

    void setThreadNum(int32_t num);

    int32_t getThreadNum() const;

    DBConnectionPool* getDBConnectionPool();

    void init();

private:
    int32_t thread_num_;
    std::vector<DBConnection*> db_service_;

    DBConnectionPool* mDBConnectionPool;
};

}



