#pragma once
#include <mutex>
#include "ILogger.h"

namespace Logging {

    class ConsoleLogger : public ILogger {
        public:
            ConsoleLogger();
            ~ConsoleLogger() override = default;

            void log(LogLevel level, const std::string& message) override;

            bool isLevelEnabled(LogLevel level) const override;
            void setLevel(LogLevel level) override;

            void flush() override;

        private:
            mutable std::mutex mutex_;
            LogLevel currentLevel_{LogLevel::Info};  // default log level

            void output(const std::string& levelStr, const std::string& message);
    };

} // namespace Logging