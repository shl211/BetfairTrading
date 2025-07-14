#pragma once
#include <string>

namespace Logging {
    enum class LogLevel {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off // disables logging
    };

    class ILogger {
    public:
        virtual ~ILogger() = default;

        virtual void log(LogLevel level, const std::string& message) = 0;

        // Convenience methods
        virtual void trace(const std::string& message) { log(LogLevel::Trace, message); }
        virtual void debug(const std::string& message) { log(LogLevel::Debug, message); }
        virtual void info(const std::string& message) { log(LogLevel::Info, message); }
        virtual void warn(const std::string& message) { log(LogLevel::Warn, message); }
        virtual void error(const std::string& message) { log(LogLevel::Error, message); }
        virtual void critical(const std::string& message) { log(LogLevel::Critical, message); }

        virtual bool isLevelEnabled(LogLevel level) const = 0;

        virtual void setLevel(LogLevel level) = 0;

        virtual void flush() = 0;
    };
}