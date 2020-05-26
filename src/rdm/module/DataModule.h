#pragma once

#include <cstdint>

namespace rdm {

class DataModule {
public:
    virtual bool init() = 0;
    virtual bool loadData() = 0;
    virtual void release() = 0;

    [[nodiscard]] virtual uint8_t status() const = 0;
};

}