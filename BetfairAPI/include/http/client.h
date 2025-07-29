#pragma once

#include <memory>
#include "Logging/ILogger.h"
#include "http/request.h"
#include "http/response.h"

namespace BetfairAPI::HTTP {
    class HTTPClient {
        public:
            
            HTTPClient(std::shared_ptr<Logging::ILogger> logger = nullptr);

            Response makeRequest(const Request& request);
        
            void setMaxRetries(int retries) { max_retries_ = retries; }
            int getMaxRetries() const noexcept { return max_retries_; }

            void setTimeout(std::chrono::milliseconds timeout) { timeout_ = timeout; }
            std::chrono::milliseconds getTimeout() const noexcept { return timeout_; }

        private:
            int max_retries_ = 3;
            std::chrono::milliseconds timeout_ = std::chrono::seconds(30);
            std::shared_ptr<Logging::ILogger> logger_ = nullptr;
    };
} // namespace BetfairAPI::HTTP
