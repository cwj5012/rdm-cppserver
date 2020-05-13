#include <catch2/catch.hpp>

#include "../../log/Logger.h"
#include "../System.h"

using namespace rdm;

// TODO linux
//TEST_CASE("System", "getProcessorCount") {
//    uint64_t min = 1;
//    uint64_t max = 1024;
//    ASSERT_LE(min, System::getProcessorCount());
//    ASSERT_GE(max, System::getProcessorCount());
//
//    LOG_DEBUG("processor count: {}",
//              System::getProcessorCount());
//}
//
//TEST_CASE(System, getTotalVirtualMemory) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min, System::getTotalVirtualMemory());
//    ASSERT_GE(max, System::getTotalVirtualMemory());
//
//    LOG_DEBUG("total virtual memory: {} GB",
//              System::getTotalVirtualMemory() / 1024 / 1024 / 1024.f);
//}
//
//TEST_CASE(System, getVirtualMemoryUsage) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min, System::getVirtualMemoryUsage());
//    ASSERT_GE(max, System::getVirtualMemoryUsage());
//
//    LOG_DEBUG("virtual memory usage: {} GB",
//              System::getVirtualMemoryUsage() / 1024 / 1024 / 1024.f);
//}
//
//TEST_CASE(System, getVirtualMemoryUsageCurrentProcess) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min, System::getVirtualMemoryUsageCurrentProcess());
//    ASSERT_GE(max, System::getVirtualMemoryUsageCurrentProcess());
//
//    LOG_DEBUG("virtual memory usage current process: {} MB",
//              System::getVirtualMemoryUsageCurrentProcess() / 1024 / 1024.f);
//}
//
//TEST_CASE(System, getTotalPhysicalMemory) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min, System::getTotalPhysicalMemory());
//    ASSERT_GE(max, System::getTotalPhysicalMemory());
//
//    LOG_DEBUG("total physical memory: {} GB",
//              System::getTotalPhysicalMemory() / 1024 / 1024 / 1024.f);
//}
//
//TEST_CASE(System, getPhysicalMemoryUsage) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min, System::getPhysicalMemoryUsage());
//    ASSERT_GE(max, System::getPhysicalMemoryUsage());
//
//    LOG_DEBUG("physical memory usage: {} GB",
//              System::getPhysicalMemoryUsage() / 1024 / 1024 / 1024.f);
//}
//
//TEST_CASE(System, gePhysicalMemoryUsageCurrentProcess) {
//    uint64_t min = 1;
//    uint64_t max = 1ULL << 63;
//    ASSERT_LE(min <= System::gePhysicalMemoryUsageCurrentProcess());
//    ASSERT_GE(max >= System::gePhysicalMemoryUsageCurrentProcess());
//
//    LOG_DEBUG("physical memory usage current process: {} MB",
//              System::gePhysicalMemoryUsageCurrentProcess() / 1024 / 1024.f);
//}
//
//TEST_CASE(System, getCpuCurrentUsage) {
//    System::initCpuCurrentUsage();
//    for (auto i = 0; i < 1 * 1000 * 1000; ++i) {
//        std::srand(0);
//    }
//    auto usage = System::getCpuCurrentUsage();
//    ASSERT_LT(0 < usage);
//    ASSERT_GE(100 >= usage);
//
//    LOG_DEBUG("cup current usage: {} %", usage);
//}
//
//TEST_CASE(System, getCpuCurrentProcessUsage) {
//    System::initCpuCurrentProcessUsage();
//    for (auto i = 0; i < 1 * 1000 * 1000; ++i) {
//        std::srand(0);
//    }
//    auto usage = System::getCpuCurrentProcessUsage();
//    ASSERT_LT(0 < usage);
//    ASSERT_GE(100 >= usage);
//
//    LOG_DEBUG("cup current process usage: {} %", usage);
//}