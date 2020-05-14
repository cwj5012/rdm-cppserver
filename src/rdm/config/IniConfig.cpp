#include "IniConfig.h"
#include "../log/Logger.h"

namespace rdm {

IniConfig::IniConfig(std::string& path)
        : path_(path) {

}

int IniConfig::parse() {
    reader_ = std::make_shared<INIReader>(path_);
    if (reader_->ParseError() < 0) {
        LOG_ERROR("Can't load '{}'", path_);
        return 1;
    }
    return 0;
}

}



