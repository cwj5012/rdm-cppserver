#include "XmlConfig.h"

namespace rdm {

XmlConfig::XmlConfig(const std::string& path)
        : path_(path) {
    doc_ = std::make_shared<tinyxml2::XMLDocument>();
}

int XmlConfig::parse() {
    if (tinyxml2::XML_SUCCESS != doc_->LoadFile(path_.c_str()))
    {
        return 1;
    }
    return 0;
}

}