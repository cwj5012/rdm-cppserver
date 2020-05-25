#pragma once

namespace rdm{

enum ExitCode : int {
    EXIT_CLEAN = 0,
    EXIT_BADOPTIONS = 2,
    EXIT_ABRUPT = 14,
};

}