 #include "YamlConfig.h"
#include "../log/Logger.h"

rdm::YamlConfig::YamlConfig(std::string&& path)
        : path_(path) {

}

rdm::YamlConfig::~YamlConfig() {
    LOG_DEBUG("{}", __PRETTY_FUNCTION__);
}

int rdm::YamlConfig::parse() {
    try {
        node_ = std::make_shared<YAML::Node>(YAML::LoadFile(path_));
        if (node_->IsNull()) {
            return kEmpty;
        }
    } catch (std::exception& ex) {
        LOG_ERROR("yaml file parse error, {}", ex.what());
        return kError;
    }
    return kOk;
}

