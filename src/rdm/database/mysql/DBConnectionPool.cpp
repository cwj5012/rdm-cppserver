#include <mutex>

#include "../../log/Logger.h"
#include "DBConnectionPool.h"
#include "DBConnection.h"

namespace rdm {


DBConnectionPool::DBConnectionPool(DatabaseLoginInfo& info)
        : mInfo(info),
          mDriver(nullptr),
          mConnection(nullptr) {

}

DBConnectionPool::~DBConnectionPool() {
    // todo 多线程问题排查
    // destroyPool();
}

void DBConnectionPool::initPool(int16_t maxCount) {
    mMaxCount = maxCount;
    mCurCount = 0;

    try {
        mDriver = get_driver_instance();
    }
    catch (sql::SQLException& /* &e */) {
        perror("get sql driver failed");
    }
    catch (std::runtime_error& /* &e */) {
        perror("run error");
    }
    initConnection(static_cast<int16_t>(maxCount / 2));
}

DBConnection* DBConnectionPool::getConnection() {
    mtx.lock();
    DBConnection* conn = nullptr;
    if (!mConnectionList.empty()) {
        conn = mConnectionList.front();
        mConnectionList.pop_front();
        if (conn->isClosed()) {
            delete conn;
            conn = createConnection();
        }

        if (conn == nullptr) {
            --mCurCount;
        }
        mtx.unlock();
        return conn;
    } else {
        if (mCurCount < mMaxCount) {
            conn = createConnection();
            if (conn) {
                ++mCurCount;
                mtx.unlock();
                return conn;
            } else {
                mtx.unlock();
                return nullptr;
            }
        } else {
            mtx.unlock();
            return nullptr;
        }
    }
}

void DBConnectionPool::releaseConnnection(DBConnection* conn) {
    if (conn) {
        mtx.lock();
        mConnectionList.push_back(conn);
        mtx.unlock();
    }
}

void DBConnectionPool::initConnection(int16_t initCount) {
    mtx.lock();
    DBConnection* conn = nullptr;
    for (int i = 0; i < initCount; ++i) {
        conn = createConnection();
        if (conn) {
            mConnectionList.push_back(conn);
            ++mCurCount;
        } else {
            perror("create connection error");
        }
    }
    LOG_INFO("database connection pool init, count: {}", initCount);
    mtx.unlock();
}

DBConnection* DBConnectionPool::createConnection() {
    DBConnection* conn = nullptr;
    try {
        conn = new DBConnection(mDriver, mInfo);
        // important 记得要调用connect方法，才能完成DBConnection的初始化，不然conn.close()会崩溃
        conn->connect();
        return conn;
    } catch (sql::SQLException /* &e */) {
        perror("link error");
        return nullptr;
    }
    catch (std::runtime_error /* &e */) {
        perror("run error");
        return nullptr;
    }
}

void DBConnectionPool::destroyConnection(DBConnection* conn) {
    if (conn) {
        try {
            conn->close();
        }
        catch (sql::SQLException& e) {
            perror(e.what());
        }
        catch (std::exception& e) {
            perror(e.what());
        }
        delete conn;
    }
}

void DBConnectionPool::destroyPool() {
    mtx.lock();
    auto it = mConnectionList.begin();
    auto itEnd = mConnectionList.end();
    for (; it != itEnd; ++it) {
        destroyConnection(*it);
    }

    mCurCount = 0;
    mConnectionList.clear();
    mtx.unlock();
}

}