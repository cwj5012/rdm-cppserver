#include "IniConfig.h"
#include "../log/Logger.h"

namespace rdm {

IniConfig::IniConfig(std::string& path)
        : path_(path) {

}

int IniConfig::parse() {
    reader_ = std::make_shared<INIReader>(path_);

    if (reader_->ParseError() < 0) {
        LOG_ERROR("Can't load '{}'",path_);
        return 1;
    }

    LOG_DEBUG("Config loaded from 'test.ini': version= {}, name={} , email={}, pi={}, active={}",
              reader_->GetInteger("protocol", "version", -1),
              reader_->Get("user", "name", "UNKNOWN"),
              reader_->Get("user", "email", "UNKNOWN"),
              reader_->GetReal("user", "pi", -1),
              reader_->GetBoolean("user", "active", true));

    return 0;
}

}



