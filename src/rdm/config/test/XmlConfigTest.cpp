#include <catch2/catch.hpp>

#include "../XmlConfig.h"

using namespace rdm;

TEST_CASE("XmlConfig", "[]") {
    std::string path{"../../src/rdm/config/test/test.xml"};
    auto xml = XmlConfig(path);
    REQUIRE(xml.parse() == 0);
    auto doc = xml.getDoc();
    auto root = doc->RootElement();
    REQUIRE(root != nullptr);
    REQUIRE(std::string(root->Value()) == "mysql");
    REQUIRE(std::string(root->FirstChildElement("ip")->GetText()) == "127.0.0.1");
    REQUIRE(std::string(root->FirstChildElement("ip")->Attribute("type")) == "ipv4");
    REQUIRE(std::string(root->FirstChildElement("port")->GetText()) == "3306");
    REQUIRE(std::string(root->FirstChildElement("database_name")->GetText()) == "mysql");
    REQUIRE(std::string(root->FirstChildElement("user")->GetText()) == "root");
    REQUIRE(std::string(root->FirstChildElement("password")->GetText()) == "1234");
}

// <mysql>
//     <ip type=ipv4>127.0.0.1</ip>
//     <port>3306</port>
//     <database_name>mysql</database_name>
//     <table_name>test</table_name>
//     <user>root</user>
//     <password>1234</password>
// </mysql>
