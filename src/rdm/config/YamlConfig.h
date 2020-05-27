#pragma once

#include <string>
#include <memory>

#include <yaml-cpp/yaml.h>

namespace rdm {

class YamlConfig {
public:
    enum {
        kOk, kEmpty, kError
    };

    explicit YamlConfig(std::string&& path);
    ~YamlConfig();

    int parse();

    [[nodiscard]] std::shared_ptr<YAML::Node> getNode() const { return node_; }

private:
    std::string data_;
    std::string path_;
    std::shared_ptr<YAML::Node> node_;
};

}

