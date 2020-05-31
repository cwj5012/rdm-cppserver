/*
 * 参考：https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
 *
 * TODO Linux 平台没封装，都返回0
 */

#pragma once

#include <thread>


namespace rdm {

/**
 * 获取 cpu 线程数，占用率，以及内存占用率
 */
class System {

public:
    /**
     * 获得 cup 逻辑个数
     */
    static int getProcessorCount();

    /**
     * 虚拟内存大小，单位字节
     */
    static uint64_t getTotalVirtualMemory();

    /**
     * 虚拟内存使用大小，单位字节
     */
    static uint64_t getVirtualMemoryUsage();

    /**
     * 当前进程使用的虚拟内存大小，单位字节
     */
    static uint64_t getVirtualMemoryUsageCurrentProcess();

    /**
     * 物理内存大小，单位字节
     */
    static uint64_t getTotalPhysicalMemory();

    /**
     * 物理内存使用大小，单位字节
     */
    static uint64_t getPhysicalMemoryUsage();

    /**
     * 当前进程使用的物理内存大小，单位字节
     */
    static uint64_t gePhysicalMemoryUsageCurrentProcess();

    /**
     * CPU利用率（初始化）
     */
    static void initCpuCurrentUsage();

    /**
     * CPU利用率（需要先调用初始化方法）
     */
    static double getCpuCurrentUsage();

    /**
     * CPU利用率，当前进程（初始化）
     */
    static void initCpuCurrentProcessUsage();

    /**
     * CPU利用率，当前进程（需要先调用初始化方法）
     */
    static double getCpuCurrentProcessUsage();

private:
#ifdef __linux__
#else
    // static PDH_HQUERY cpuQuery_;
    // static PDH_HCOUNTER cpuTotal_;
    //
    // static ULARGE_INTEGER lastCPU_;
    // static ULARGE_INTEGER lastSysCPU_;
    // static ULARGE_INTEGER lastUserCPU_;
    // static int numProcessors_;
    // static HANDLE self_;
#endif
}; // class System

} // namespace rdm
