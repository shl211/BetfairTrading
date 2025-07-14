#include "Logging/file_logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/ostr.h>  // if you log custom types via `<<`

namespace Logging {

    namespace {
        // Helper to convert your enum to spdlog level
        spdlog::level::level_enum toSpdLogLevel(LogLevel level) {
            switch (level) {
                case LogLevel::Trace:    return spdlog::level::trace;
                case LogLevel::Debug:    return spdlog::level::debug;
                case LogLevel::Info:     return spdlog::level::info;
                case LogLevel::Warn:     return spdlog::level::warn;
                case LogLevel::Error:    return spdlog::level::err;
                case LogLevel::Critical: return spdlog::level::critical;
                default:                 return spdlog::level::info;
            }
        }
    }

    SpdFileLogger::SpdFileLogger(const std::string& filename)
    {
        logger_ = spdlog::basic_logger_mt("file_logger", filename);
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        logger_->set_level(spdlog::level::info); // Default level
    }

    void SpdFileLogger::trace(const std::string& msg) { logger_->trace(msg); }
    void SpdFileLogger::debug(const std::string& msg) { logger_->debug(msg); }
    void SpdFileLogger::info(const std::string& msg) { logger_->info(msg); }
    void SpdFileLogger::warn(const std::string& msg) { logger_->warn(msg); }
    void SpdFileLogger::error(const std::string& msg) { logger_->error(msg); }
    void SpdFileLogger::critical(const std::string& msg) { logger_->critical(msg); }

    void SpdFileLogger::log(LogLevel level, const std::string& msg) {
        logger_->log(toSpdLogLevel(level), msg);
    }

    bool SpdFileLogger::isLevelEnabled(LogLevel level) const {
        return logger_->should_log(toSpdLogLevel(level));
    }

    void SpdFileLogger::setLevel(LogLevel level) {
        logger_->set_level(toSpdLogLevel(level));
    }

    void SpdFileLogger::flush() {
        logger_->flush();
    }

} // namespace Logging
