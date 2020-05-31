#pragma once

#include <string>

#ifdef _WIN32
#include <json/json.h>
#else
#include <jsoncpp/json/json.h>
#endif
namespace rdm {

class JsonConfig {
public:
    explicit JsonConfig(const std::string& path);
    ~JsonConfig() = default;

    int parse();

    Json::Value getRoot() const { return root_; }

private:
    std::string data_;
    std::string path_;
    Json::Value root_;
};

}


