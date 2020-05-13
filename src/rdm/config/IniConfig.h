#pragma once

#include <string>
#include <memory>

#include <INIReader.h>

namespace rdm {

class IniConfig {
public:
    explicit IniConfig(std::string& path);
    ~IniConfig() = default;

    int parse();
    int parseStr() = delete;

private:
    std::string data_;
    std::string path_;
    std::shared_ptr<INIReader> reader_;
};

}


