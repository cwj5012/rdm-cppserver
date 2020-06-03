#include "Options.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

namespace rdm {

// copy_if was left out of the C++03 standard, so mimic the C++11
// behavior to support all predicate types.  The alternative is to
// use remove_copy_if, but it only works for adaptable functors.
template<typename InputIterator,
        typename OutputIterator,
        typename Predicate>
OutputIterator
copy_ifx(InputIterator first,
         InputIterator last,
         OutputIterator result,
         Predicate pred) {
    while (first != last) {
        if (pred(*first))
            *result++ = *first;
        ++first;
    }
    return result;
}

/// @brief Tokenize a string.  The tokens will be separated by each non-quoted
///        space or equal character.  Empty tokens are removed.
///
/// @param input The string to tokenize.
///
/// @return Vector of tokens.
std::vector<std::string> tokenize(const std::string& input) {
    typedef boost::escaped_list_separator<char> separator_type;
    separator_type separator("\\",    // The escape characters.
                             "= ",    // The separator characters.
                             "\"\'"); // The quote characters.

    // Tokenize the intput.
    boost::tokenizer<separator_type> tokens(input, separator);

    // Copy non-empty tokens from the tokenizer into the result.
    std::vector<std::string> result;
    copy_ifx(tokens.begin(), tokens.end(), std::back_inserter(result),
             !boost::bind(&std::string::empty, _1));
    return result;
}

namespace po = boost::program_options;

Options::Options() {

}

Options::~Options() {

}

bool Options::init() {
    std::string a;
    uint32_t port;
    desc_.add_options()
            ("address", po::value<std::string>(&a))
            ("port", po::value<uint32_t>(&port));

    return true;
}

void Options::parse(const std::string& cmd) {
    po::store(po::command_line_parser(tokenize(cmd)).options(desc_).run(), vm_);
    po::notify(vm_);
}

void Options::reset() {
    vm_.clear();
}

void Options::release() {

}

}
