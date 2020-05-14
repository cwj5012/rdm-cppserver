#include <tinyxml2.h>

#include "../log/Logger.h"
#include "ServerNetConfig.h"

namespace rdm {

ServerNetConfig::ServerNetConfig() {

}

ServerNetConfig::~ServerNetConfig() {

}

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
    return &mInfo;
}

void ServerNetConfig::setPath(const std::string& path) {
    mConfigPath = path;
}

bool ServerNetConfig::load() {
    tinyxml2::XMLDocument doc;
    if (tinyxml2::XML_SUCCESS != doc.LoadFile((mConfigPath).c_str())) {
        LOG_ERROR("load xml file error");
        return false;
    }

    tinyxml2::XMLElement* rootEle = doc.RootElement();
    if (!rootEle) {
        LOG_ERROR("get root element error");
        return false;
    }

    tinyxml2::XMLElement* ele1 = rootEle->FirstChildElement("System");
    if (!ele1) {
        LOG_ERROR("get System element error");
        return false;
    }

    mInfo.system_id = ele1->UnsignedAttribute("ID");
    mInfo.system_type = ele1->UnsignedAttribute("Type");
    mInfo.system_name = ele1->Attribute("Name");

    tinyxml2::XMLElement* ele2 = rootEle->FirstChildElement("Listen");
    if (!ele2) {
        LOG_ERROR("get Listen element error");
        return false;
    }
    for (tinyxml2::XMLElement* e = ele2->FirstChildElement("List");
         e != nullptr;
         e = e->NextSiblingElement("List")) {
        auto id = e->UnsignedAttribute("ID");
        auto ip = e->Attribute("IP");
        auto port = e->Attribute("PORT");
        mInfo.listen_list[id] = HostInfo(ip, port);
    }


    tinyxml2::XMLElement* ele3 = rootEle->FirstChildElement("Connect");
    if (!ele3) {
        LOG_ERROR("get Connect element error");
        return false;
    }
    for (tinyxml2::XMLElement* e = ele3->FirstChildElement("List");
         e != nullptr;
         e = e->NextSiblingElement("List")) {
        auto id = e->UnsignedAttribute("ID");
        auto ip = e->Attribute("IP");
        auto port = e->Attribute("PORT");
        mInfo.connect_list[id] = HostInfo(ip, port);
    }

    tinyxml2::XMLElement* ele4 = rootEle->FirstChildElement("Mysql");
    if (!ele4) {
        LOG_ERROR("get Mysql element error");
        return false;
    }
    auto host = ele4->Attribute("Host");
    auto port = ele4->Attribute("Port");
    auto user_name = ele4->Attribute("UserName");
    auto password = ele4->Attribute("Password");
    auto db_name = ele4->Attribute("DBName");
    mInfo.mysql_info = MysqlInfo(host, port, user_name, password, db_name);

    return true;
}

}
