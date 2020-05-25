#pragma once

#include "ExitCode.h"

namespace rdm {

struct ShutdownTaskArgs {
    // This should be set to true if we called shutdown from the shutdown command
    bool isUserInitiated = false;
};

ExitCode waitForShutdown();

class Exit {

};

}


