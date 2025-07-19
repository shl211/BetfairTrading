#include "Logging/coloured_console_logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Logging {

    ColouredConsoleLogger::ColouredConsoleLogger() {
        // Create a color multi-threaded logger to console
        logger_ = spdlog::stdout_color_mt("console");
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
        logger_->set_level(toSpdLevel(currentLevel_));
    }

    void ColouredConsoleLogger::log(LogLevel level, const std::string& message) {
        if (!isLevelEnabled(level)) {
            return;
        }
        logger_->log(toSpdLevel(level), message);
    }

    bool ColouredConsoleLogger::isLevelEnabled(LogLevel level) const {
        return static_cast<int>(level) >= static_cast<int>(currentLevel_);
    }

    void ColouredConsoleLogger::setLevel(LogLevel level) {
        currentLevel_ = level;
        logger_->set_level(toSpdLevel(level));
    }

    void ColouredConsoleLogger::flush() {
        logger_->flush();
    }

    spdlog::level::level_enum ColouredConsoleLogger::toSpdLevel(LogLevel level) const {
        switch(level) {
            case LogLevel::Trace: return spdlog::level::trace;
            case LogLevel::Debug: return spdlog::level::debug;
            case LogLevel::Info: return spdlog::level::info;
            case LogLevel::Warn: return spdlog::level::warn;
            case LogLevel::Error: return spdlog::level::err;
            case LogLevel::Critical: return spdlog::level::critical;
            default: return spdlog::level::info;
        }
    }

} // namespace Logging
