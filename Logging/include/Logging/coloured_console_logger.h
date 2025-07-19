#pragma once
#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include "ILogger.h"

namespace Logging {

    class ColouredConsoleLogger : public ILogger {
        public:
            ColouredConsoleLogger();
            ~ColouredConsoleLogger() override = default;

            void log(LogLevel level, const std::string& message) override;

            bool isLevelEnabled(LogLevel level) const override;
            void setLevel(LogLevel level) override;

            void flush() override;

        private:
            std::shared_ptr<spdlog::logger> logger_;
            LogLevel currentLevel_{LogLevel::Info};

            spdlog::level::level_enum toSpdLevel(LogLevel level) const;
    };

} // namespace Logging
