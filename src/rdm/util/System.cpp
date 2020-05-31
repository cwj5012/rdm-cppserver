#ifdef __linux__
#include <sys/sysinfo.h>
#else
#endif

#include <fstream>
#include <cstring>

#include "System.h"

namespace rdm {

static int parseLine(char* line) {
#ifdef __linux__
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p < '0' || *p > '9')
        p++;
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
#endif
    return 0;
}


int System::getProcessorCount() {
    return std::thread::hardware_concurrency();
}

uint64_t System::getTotalVirtualMemory() {
#ifdef __linux__
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
#endif
    return 0;
}

uint64_t System::getVirtualMemoryUsage() {
#ifdef __linux__
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
#endif
    return 0;
}

uint64_t System::getVirtualMemoryUsageCurrentProcess() {
#ifdef __linux__
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "VmSize:", 7) == 0) {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
#endif
    return 0;
}

uint64_t System::getTotalPhysicalMemory() {
#ifdef __linux__
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
#endif
    return 0;
}

uint64_t System::getPhysicalMemoryUsage() {
#ifdef __linux__
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
#endif
    return 0;
}

uint64_t System::gePhysicalMemoryUsageCurrentProcess() {
#ifdef __linux__
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
#endif
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