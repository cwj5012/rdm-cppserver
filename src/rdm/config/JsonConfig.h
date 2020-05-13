#pragma once

#include <string>

#include <jsoncpp/json/json.h>

namespace rdm {

class JsonConfig {
public:
    explicit JsonConfig(const std::string& path);
    ~JsonConfig() = default;

    int parse();

private:
    std::string data_;
    std::string path_;
    Json::Value root_;
};

}


