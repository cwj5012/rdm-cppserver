#include "DBConnection.h"

namespace rdm
{


    DBConnection::DBConnection(sql::Driver* driver, const DatabaseLoginInfo& info)
            : info_(info),
              driver_(driver),
              con_(nullptr),
              stmt_(nullptr),
              res_(nullptr),
              prep_stmt_(nullptr)
    {

    }

    DBConnection::~DBConnection()
    {
        delete prep_stmt_;
        delete res_;
        delete stmt_;
        delete con_;
    }

    void DBConnection::connect()
    {
        try
        {
            driver_ = get_driver_instance();
            con_ = driver_->connect("tcp://127.0.0.1:3306", "root", "1234");
            stmt_ = con_->createStatement();
        } catch (sql::SQLException& e)
        {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line "
                      << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
    }

    bool DBConnection::execute()
    {
        try
        {
            return stmt_->execute(stmt_str_);
        } catch (sql::SQLException& e)
        {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line "
                      << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return false;
        }

    }

    bool DBConnection::execute(const std::string& statement)
    {
        try
        {
            return stmt_->execute(statement);
        } catch (sql::SQLException& e)
        {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line "
                      << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return false;
        }
    }

    void DBConnection::executeQuery()
    {
        try
        {
            res_ = stmt_->executeQuery(stmt_str_);
        } catch (sql::SQLException& e)
        {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line "
                      << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
    }

    void DBConnection::executeQuery(const std::string& statement)
    {
        delete res_;
        try
        {
            res_ = stmt_->executeQuery(statement);
        } catch (sql::SQLException& e)
        {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line "
                      << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
    }

    sql::ResultSet* DBConnection::result() const
    {
        return res_;
    }

    bool DBConnection::isClosed()
    {
        return con_->isClosed();
    }

    void DBConnection::close()
    {
        con_->close();
    }

    DBConnection* DBConnection::getConnection()
    {
        return this;
    }

}