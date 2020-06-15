#pragma once

#include <cstdint>
#include <mutex>

#include <boost/program_options.hpp>

namespace rdm {

class Options {
public:
    Options();
    ~Options();

    bool init();
    [[nodiscard]] bool parse(const std::string& cmd);
    void reset();
    void release();
    void showUsage();

    void add(const char* name, const boost::program_options::value_semantic* s, const char* description = nullptr);

    [[nodiscard]] boost::program_options::variables_map getValues() const { return vm_; }

private:
    boost::program_options::options_description desc_;
    boost::program_options::variables_map vm_;
};

}

