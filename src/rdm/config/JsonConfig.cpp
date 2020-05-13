#include <fstream>

#include "JsonConfig.h"
#include "../log/Logger.h"

namespace rdm {

JsonConfig::JsonConfig(const std::string& path)
        : path_(path) {

}

int JsonConfig::parse() {
    std::ifstream config_doc(path_, std::ifstream::binary);
    config_doc >> root_;
    LOG_DEBUG("{}", root_["my-encoding"].asString());
    return 0;
}

}