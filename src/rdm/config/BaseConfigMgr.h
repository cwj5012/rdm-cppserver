#pragma once

#include <cstdint>
#include <map>

#include "BaseConfig.h"

namespace rdm {

/**
 * 模块配置加载管理类
 */
class BaseConfigMgr {
public:
    BaseConfigMgr() = default;

    virtual ~BaseConfigMgr() = default;

    virtual bool init();

    virtual bool reload(uint32_t type);

    virtual bool reload();

    BaseConfig* getBaseConfig(uint32_t type) const;

private:
    virtual void bindConfig() = 0;

protected:
    std::map<uint32_t, BaseConfig*> mConfig;
};

}