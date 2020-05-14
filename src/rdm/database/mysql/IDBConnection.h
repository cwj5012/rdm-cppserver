#pragma once

#include <string>
#include <functional>
#include <cstdint>

typedef std::function<void(/* dbtool::PSQL_RESULT result, int32_t nThreadId*/)> ReadData_CallBack;
typedef std::function<void(/* int32_t nMaxRecord, int32_t nReadRecord */)> DataReady_CallBack;

// 数据库同步操作类型
enum SynSqlOptType {
    SSOT_SELECT,
    SSOT_INSERT,
    SSOT_UPDATE,
    SSOT_DELECT,
};

// 数据库登录信息
struct DatabaseLoginInfo {
    std::string ip;                         // 数据库IP
    std::string name;                       // 数据库登陆账号
    std::string passwd;                     // 数据库登陆密码
    std::string db_name;                    // 数据库名称
    uint32_t port;                       // 数据库端口

    DatabaseLoginInfo()
            : port(0) {}
};

// 异步数据加载请求
struct DataLoadRequest {

    DatabaseLoginInfo db_login_info;

    int32_t thread_num;                 // 线程个数
    std::string sql_select_max_record;      // 读取最大记录条数的SQL语句
    std::string sql_select_data;            // 读取数据的SQL语句
    ReadData_CallBack f_readdata;                 // 数据读取回调
    DataReady_CallBack f_dataready;                // 数据读取完毕回调

    DataLoadRequest()
            : thread_num(1),
              f_readdata(NULL),
              f_dataready(NULL) {}
};

// 同步数据加载请求
struct SynDataLoadRequest {
    DatabaseLoginInfo db_login_info;

    SynSqlOptType optType;                  // 操作类型
    std::string sql_select_data;            // 读取数据的SQL语句
    ReadData_CallBack f_readdata;           // 数据读取回调

    SynDataLoadRequest()
            : optType(SSOT_SELECT),
              f_readdata(NULL) {}
};

struct SynExecuteRequest {
    DatabaseLoginInfo db_login_info;

    std::string szSQL;                      // SQL语句

    SynExecuteRequest() = default;
};
