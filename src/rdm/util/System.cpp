#include <sys/sysinfo.h>
#include <fstream>

#include "System.h"

namespace rdm {

int System::getProcessorCount() {
    return std::thread::hardware_concurrency();
}

uint64_t System::getTotalVirtualMemory() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token) {
        if (token == "SwapTotal:") {
            unsigned long mem;
            if (file >> mem) {
                return mem * 1024;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // nothing found
}

uint64_t System::getVirtualMemoryUsage() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token) {
        if (token == "SwapFree:") {
            unsigned long mem;
            if (file >> mem) {
                return getTotalVirtualMemory() - mem * 1024;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // nothing found
}

uint64_t System::getVirtualMemoryUsageCurrentProcess() {
    return 0;
}

uint64_t System::getTotalPhysicalMemory() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token) {
        if (token == "MemTotal:") {
            unsigned long mem;
            if (file >> mem) {
                return mem * 1024;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // nothing found

}

uint64_t System::getPhysicalMemoryUsage() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token) {
        if (token == "MemAvailable:") {
            unsigned long mem;
            if (file >> mem) {
                return getTotalPhysicalMemory() - mem * 1024;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // nothing found
}

uint64_t System::gePhysicalMemoryUsageCurrentProcess() {
    return 0;

}

void System::initCpuCurrentUsage() {

}

double System::getCpuCurrentUsage() {
    return 0;
}

void System::initCpuCurrentProcessUsage() {

}

double System::getCpuCurrentProcessUsage() {
    return 0;
}

} // namespace pandax