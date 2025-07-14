#include <memory>
#include <spdlog/spdlog.h>
#include "ILogger.h"

namespace Logging {
    class SpdFileLogger : public ILogger {
    public:
        SpdFileLogger(const std::string& filename);
        void trace(const std::string& msg) override;
        void debug(const std::string& msg) override;
        void info(const std::string& msg) override;
        void warn(const std::string& msg) override;
        void error(const std::string& msg) override;
        void critical(const std::string& msg) override;
        void log(LogLevel level, const std::string& msg) override;
        bool isLevelEnabled(LogLevel level) const override;
        void setLevel(LogLevel level) override;
        void flush() override;
    
    private:
        std::shared_ptr<spdlog::logger> logger_;
    };

}