#include "Logger.h"

#include <iostream>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

const int32_t MAX_ROTATING_FILE_SIZE = 1024 * 1024 * 10; // 10MB
const int32_t MAX_ROTATING_FILE_COUNT = 999;

Logger::Logger()
        : console_logger_(nullptr), basic_file_logger_(nullptr), rotating_file_logger_(nullptr),
          daily_file_logger_(nullptr) {
    try {
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%Y-%m-%d] [%T.%f] [%^%-6l%$] %v");
        console_logger_ = spdlog::stdout_color_mt("console_logger_");
        // basic_file_logger_ = spdlog::basic_logger_mt("basic_file_logger_", "basic_file_log.log");
        // rotating_file_logger_ = spdlog::rotating_logger_mt("rotating_file_logger_", "rotating_file_log.log"
        // 	, MAX_ROTATING_FILE_SIZE
        // 	, MAX_ROTATING_FILE_COUNT);
        daily_file_logger_ = spdlog::daily_logger_mt("daily_file_logger_", "daily_log.log");
    }
    catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Logger::~Logger() {
    spdlog::drop("console_logger_");
    spdlog::drop("basic_file_logger_");
    spdlog::drop("rotating_file_logger_");
    spdlog::drop("daily_file_logger_");

    // spdlog::drop_all();
}

void Logger::setLevel(spdlog::level::level_enum level) {
    spdlog::set_level(level);
}