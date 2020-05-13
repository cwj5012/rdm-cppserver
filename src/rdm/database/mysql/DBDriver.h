/*
 * 封装 sql::Driver 类
 * 线程安全
 */

#pragma once

#include <mutex>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace rdm {

static std::mutex driver_mutex;

class DBDriver {
public:
    DBDriver();

    ~DBDriver() = default;

    int32_t getMajorVersion();

    int32_t getMinorVersion();

    int32_t getPatchVersion();

    const std::string getName();

    void threadInit();

    void threadEnd();

    sql::Driver* getDriver();

private:
    sql::Driver* mDriver;
};

}




