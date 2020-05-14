#pragma once

#include <string>
#include <memory>

#include <tinyxml2.h>

namespace rdm{

class XmlConfig {
public:
    XmlConfig(const std::string& path);
    ~XmlConfig() = default;

    int parse();

    std::shared_ptr<tinyxml2::XMLDocument> getDoc() const{ return doc_; }

private:
    std::string data_;
    std::string path_;
    std::shared_ptr<tinyxml2::XMLDocument> doc_;
};

}
