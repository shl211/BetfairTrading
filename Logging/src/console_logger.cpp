#include "Logging/console_logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace Logging {

    ConsoleLogger::ConsoleLogger() = default;

    void ConsoleLogger::log(LogLevel level, const std::string& message) {
        if (!isLevelEnabled(level)) {
            return;
        }

        std::string levelStr;
        switch (level) {
            case LogLevel::Trace: levelStr = "TRACE"; break;
            case LogLevel::Debug: levelStr = "DEBUG"; break;
            case LogLevel::Info: levelStr = "INFO"; break;
            case LogLevel::Warn: levelStr = "WARN"; break;
            case LogLevel::Error: levelStr = "ERROR"; break;
            case LogLevel::Critical: levelStr = "CRITICAL"; break;
        }

        output(levelStr, message);
    }

    bool ConsoleLogger::isLevelEnabled(LogLevel level) const {
        return static_cast<int>(level) >= static_cast<int>(currentLevel_);
    }

    void ConsoleLogger::setLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        currentLevel_ = level;
    }

    void ConsoleLogger::flush() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << std::flush;
    }

    void ConsoleLogger::output(const std::string& levelStr, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);

        // Get current time
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
#if defined(_MSC_VER)
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm);
#endif

        std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
                  << "[" << levelStr << "] "
                  << message << std::endl;
    }

} // namespace Logging
