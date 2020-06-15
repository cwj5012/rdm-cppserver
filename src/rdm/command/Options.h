#pragma once

#include <stdint.h>

#include <boost/program_options.hpp>

#ifdef __linux__
#else

#include <windows.h>
#include <shellapi.h>

#endif

namespace rdm {

static int shellParseArgv(const std::string& s, int& argc_out, char** argv_out) {
#ifdef __linux__
#else
    LPWSTR* szArglist;
    int nArgs;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (nullptr == szArglist) {
        wprintf(L"CommandLineToArgvW failed\n");
        return 0;
    } else {
        for (int i = 0; i < nArgs; i++)
            sprintf(argv_out[i], "%ws", szArglist[i]);
    }

    LocalFree(szArglist);
#endif
}

class Options {
public:
    Options();
    ~Options();

    bool init();
    [[nodiscard]] bool parse(const std::string& cmd);
    void reset();
    void release();
    void showUsage();

    [[nodiscard]] boost::program_options::variables_map getValues() const { return vm_; }

private:
    boost::program_options::options_description desc_;
    boost::program_options::variables_map vm_;
};

}

