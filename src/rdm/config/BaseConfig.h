#pragma once

#include <cstdint>
#include <string>

namespace rdm {

/*
 * 模块配置加载基类
 */
class BaseConfig {
public:
    BaseConfig() = default;

    virtual ~BaseConfig() = default;

    virtual bool init() = 0;

    virtual bool reload() = 0;

    virtual uint32_t getConfigType() const = 0;

    virtual std::string getConfigName() const = 0;
};

}
