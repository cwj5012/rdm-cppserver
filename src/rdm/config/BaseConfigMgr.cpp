#include "BaseConfigMgr.h"
#include "../log/Logger.h"

namespace rdm {

bool BaseConfigMgr::init() {
    mConfig.clear();

    bindConfig();

    for (auto& item : mConfig) {
        auto* config = item.second;
        if (config == nullptr) {
            LOG_ERROR("config is null, type: {}", item.first);
            return false;
        }

        if (!config->init()) {
            LOG_ERROR("init config file failed, type: {}", item.first);
        }
    }
    return true;
}

bool BaseConfigMgr::reload(uint32_t type) {
    auto it = mConfig.find(type);
    if (it != mConfig.end()) {
        auto* config = it->second;
        if (config == nullptr) {
            return false;
        }
        config->reload();
    }

    return true;
}

bool BaseConfigMgr::reload() {
    for (auto item : mConfig) {
        auto* config = item.second;
        if (config == nullptr) {
            return false;
        }
        config->reload();
    }

    return true;
}

BaseConfig* BaseConfigMgr::getBaseConfig(uint32_t type) const {
    auto it = mConfig.find(type);
    if (it == mConfig.end()) {
        return nullptr;
    }
    return it->second;
}

}