#pragma once

#include <cstdint>
#include <list>

#include "DBConnection.h"

namespace rdm {

class DBConnectionPool {
public:
    DBConnectionPool(DatabaseLoginInfo& info);

    ~DBConnectionPool();

    void initPool(int16_t maxCount);

    DBConnection* getConnection();

    void releaseConnnection(DBConnection* db_service);

private:
    void initConnection(int16_t initCount);

    DBConnection* createConnection();

    void destroyConnection(DBConnection* conn);

    void destroyPool();

    DatabaseLoginInfo mInfo;

    int16_t mMaxCount;
    int16_t mCurCount;

    sql::Driver* mDriver;
    DBConnection* mConnection;
    std::list<DBConnection*> mConnectionList;
};

}




