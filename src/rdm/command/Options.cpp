#include "Options.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "../log/Logger.h"

namespace rdm {

namespace po = boost::program_options;

Options::Options()
        : desc_("xxxxxxxxxxxxx") {

}

Options::~Options() {

}

bool Options::init() {
    desc_.add_options()("help,h", "111");
    desc_.add_options()("help,h", "111");
    desc_.add_options()("address,a", po::value<std::string>(), "222");
    desc_.add_options()("port,p", po::value<std::vector<std::string>>()->multitoken(), "333");
    desc_.add_options()("command,c", po::value<std::string>()->multitoken(), "send command");

    return true;
}

bool Options::parse(const std::string& cmd) {
    try {
        std::vector<std::string> parsedInput;
        boost::split(parsedInput, cmd, boost::is_any_of(" "), boost::token_compress_on);

        std::vector<char const*> args{"command"};
        for (auto& arg : parsedInput)
            args.push_back(arg.c_str());

        po::store(po::parse_command_line(args.size(), args.data(), desc_), vm_);
        po::notify(vm_);
    } catch (std::exception& ex) {
        LOG_ERROR("{}", ex.what());
        return false;
    }

    // for (const auto& it : vm_) {
    //     std::cout << it.first.c_str() << ": ";
    //     auto& value = it.second.value();
    //     if (auto v = boost::any_cast<uint32_t>(&value))
    //         std::cout << *v;
    //     else if (auto v = boost::any_cast<std::string>(&value))
    //         std::cout << *v;
    //     else
    //         std::cout << "error";
    //     std::cout << std::endl;
    // }

    if (vm_.count("port")) {
        std::cout << "size: " << vm_["port"].as<std::vector<std::string>>().size();
    }
    std::cout << std::endl;

    if (vm_.count("help")) {
        showUsage();
    }

    return true;
}

void Options::reset() {
    vm_.clear();
}

void Options::release() {

}

void Options::showUsage() {
    std::stringstream ss;
    ss << desc_;
    LOG_INFO("\n{}", ss.str());
}

}
