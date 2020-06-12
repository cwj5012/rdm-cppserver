#pragma once

#include <utility>
#include <cstdint>
#include <string>
#include <map>

#include "BaseConfig.h"

namespace rdm {

struct HostInfo {
    std::string ip;
    std::string port;

    HostInfo() = default;

    HostInfo(std::string ip,
             std::string port)
            : ip(std::move(ip)),
              port(std::move(port)) {}
};

struct MysqlInfo {
    std::string host;
    std::string port;
    std::string user_name;
    std::string password;
    std::string db_name;

    MysqlInfo() = default;

    MysqlInfo(std::string host,
              std::string port,
              std::string user_name,
              std::string password,
              std::string db_name)
            : host(std::move(host)),
              port(std::move(port)),
              user_name(std::move(user_name)),
              password(std::move(password)),
              db_name(std::move(db_name)) {}
};

struct ServerNetInfo {
    uint32_t system_id;
    uint32_t system_type;
    std::string system_name;
    std::map<uint32_t, HostInfo> listen_list;
    std::map<uint32_t, HostInfo> connect_list;
    MysqlInfo mysql_info;

    ServerNetInfo()
            : system_id(0),
              system_type(0) {}
};

/**
 * 服务器连接配置
 *
 * 监听本机的地址/端口
 * 连接目标主机的地址/端口
 */
class ServerNetConfig : public BaseConfig {
public:
    ServerNetConfig() = default;
    ~ServerNetConfig() override = default;

    static ServerNetConfig* inst() {
        static ServerNetConfig obj;
        return &obj;
    }

    bool init() override;
    bool reload() override;

    uint32_t getConfigType() const override;
    std::string getConfigName() const override;

    ServerNetInfo* getServerNetInfo();

    void setPath(const std::string& path);
    void setKey(const std::string& key);

private:
    bool load();

    std::string path_;
    std::string key_{"server"};
    ServerNetInfo info_;
};

}

