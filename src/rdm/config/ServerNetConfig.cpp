#include "../log/Logger.h"
#include "ServerNetConfig.h"
#include "../config/YamlConfig.h"

namespace rdm {

bool ServerNetConfig::init() {
    return load();
}

bool ServerNetConfig::reload() {
    return load();
}

uint32_t ServerNetConfig::getConfigType() const {
    return 0;
}

std::string ServerNetConfig::getConfigName() const {
    return std::string();
}

ServerNetInfo* ServerNetConfig::getServerNetInfo() {
    return &info_;
}

void ServerNetConfig::setPath(const std::string& path) {
    path_ = path;
}

void ServerNetConfig::setKey(const std::string& key) {
    key_ = key;
}

bool ServerNetConfig::load() {
    std::string path{path_};
    auto yaml = YamlConfig(std::move(path));
    if (yaml.parse() != 0) {
        LOG_ERROR("load yaml file error.");
        return false;
    }
    auto node = yaml.getNode();
    if (node->IsNull()) {
        LOG_ERROR("yaml data is null.");
        return false;
    }

    info_.system_id = (*node)[key_]["id"].as<uint32_t>();
    info_.system_type = (*node)[key_]["type"].as<uint32_t>();
    info_.system_name = (*node)[key_]["name"].as<std::string>();

    for (auto item:(*node)[key_]["listen"]) {
        auto id = item["id"].as<uint32_t>();
        auto ip = item["ip"].as<std::string>();
        auto port = item["port"].as<std::string>();
        info_.listen_list[id] = HostInfo(ip, port);
    }

    for (auto item:(*node)[key_]["connect"]) {
        auto id = item["id"].as<uint32_t>();
        auto ip = item["ip"].as<std::string>();
        auto port = item["port"].as<std::string>();
        info_.connect_list[id] = HostInfo(ip, port);
    }

    auto mysql_config = (*node)[key_]["db"]["mysql"];
    if (mysql_config.IsDefined()) {
        auto host = mysql_config["host"].as<std::string>();
        auto port = mysql_config["port"].as<std::string>();
        auto user_name = mysql_config["user"].as<std::string>();
        auto password = mysql_config["passwd"].as<std::string>();
        auto db_name = mysql_config["schema"].as<std::string>();
        info_.mysql_info = MysqlInfo(host, port, user_name, password, db_name);
    }

    return true;
}

}
