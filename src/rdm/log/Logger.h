#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

#include <boost/core/noncopyable.hpp>

constexpr const char* file_name(const char* path) {
    const char* file = path;
    while (*path) {
#ifdef __linux__
        if (*path++ == '/') {
            file = path;
        }
#else
        if (*path++ == '\\') {
            file = path;
        }
#endif
    }
    return file;
}

#define LOG_TRACE(fmt, ...)                                                            \
    Logger::getLogger().trace(fmt, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...)                                                            \
    Logger::getLogger().debug(fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...)                                                            \
    Logger::getLogger().info(fmt, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...)                                                            \
    Logger::getLogger().warn("{}:{} " fmt, file_name(__FILE__), __LINE__,  ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...)                                                            \
    Logger::getLogger().error("{}:{} " fmt, file_name(__FILE__), __LINE__,  ##__VA_ARGS__)

class Logger : boost::noncopyable {
public:
    Logger();
    ~Logger();

    static Logger& getLogger() {
        static Logger lg;
        return lg;
    }

    void setLevel(spdlog::level::level_enum level);

    /** 输出到控制台和文件，Release 模式下无效 */
    template<typename... Args>
    void trace(const char* fmt, const Args& ... args);

    /** 输出到控制台和文件，Release 模式下无效 */
    template<typename... Args>
    void debug(const char* fmt, const Args& ... args);

    /** 输出到控制台和文件，Release 模式下只输出到文件 */
    template<typename... Args>
    void info(const char* fmt, const Args& ... args);

    /** 输出到控制台和文件，Release 模式下只输出到文件 */
    template<typename... Args>
    void warn(const char* fmt, const Args& ... args);

    /** 输出到控制台和文件，Release 模式下只输出到文件 */
    template<typename... Args>
    void error(const char* fmt, const Args& ... args);

private:
    std::shared_ptr<spdlog::logger> console_logger_;        // 输出控制台
    std::shared_ptr<spdlog::logger> basic_file_logger_;        // 暂时不用，输出到文件
    std::shared_ptr<spdlog::logger> rotating_file_logger_;    // 暂时不用，输出到固定大小文件，超过则自动创建新文件
    std::shared_ptr<spdlog::logger> daily_file_logger_;        // 输出到每日文件
};

template<typename ...Args>
void Logger::trace(const char* fmt, const Args& ...args) {
#ifndef NDEBUG
    console_logger_->trace(fmt, args...);
    daily_file_logger_->trace(fmt, args...);
#endif
}

template<typename ...Args>
void Logger::debug(const char* fmt, const Args& ...args) {
#ifndef NDEBUG
    console_logger_->debug(fmt, args...);
    daily_file_logger_->debug(fmt, args...);
#endif
}

template<typename ...Args>
void Logger::info(const char* fmt, const Args& ...args) {
#ifndef NDEBUG
    console_logger_->info(fmt, args...);
#endif
    daily_file_logger_->info(fmt, args...);
}

template<typename ... Args>
void Logger::warn(const char* fmt, const Args& ... args) {
#ifndef NDEBUG
    console_logger_->warn(fmt, args...);
#endif
    daily_file_logger_->warn(fmt, args...);
}

template<typename ...Args>
void Logger::error(const char* fmt, const Args& ...args) {
#ifndef NDEBUG
    console_logger_->error(fmt, args...);
#endif
    daily_file_logger_->error(fmt, args...);
}
