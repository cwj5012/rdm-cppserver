#include <ctime>

#include "Time.h"

namespace rdm {

int64_t Time::getTimeStamp() {
    return std::time(nullptr);
}

}
