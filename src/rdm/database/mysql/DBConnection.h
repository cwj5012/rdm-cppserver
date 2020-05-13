#pragma once

#include <mutex>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "IDBConnection.h"

namespace rdm {

static std::mutex mtx;

class DBConnection {
public:
    explicit DBConnection(sql::Driver* driver, const DatabaseLoginInfo& info);

    ~DBConnection();

    void connect();

    bool execute();

    bool execute(const std::string& statement);

    void executeQuery();

    void executeQuery(const std::string& statement);

    sql::ResultSet* result() const;

    bool isClosed();

    void close();

    DBConnection* getConnection();

private:
    DatabaseLoginInfo info_;
    std::string stmt_str_;

    sql::Driver* driver_;
    sql::Connection* con_;
    sql::Statement* stmt_;
    sql::ResultSet* res_;
    sql::PreparedStatement* prep_stmt_;
};

}