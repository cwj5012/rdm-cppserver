#pragma once

#include <boost/program_options.hpp>

namespace rdm {

class Options {
public:
    Options();
    ~Options();

    bool init();
    void parse(const std::string& cmd);
    void reset();
    void release();

    [[nodiscard]] boost::program_options::variables_map getValues() const { return vm_; }

private:
    boost::program_options::options_description desc_;
    boost::program_options::variables_map vm_;
};

}

