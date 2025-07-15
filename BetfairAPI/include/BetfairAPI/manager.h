#pragma once

#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>

#include "Logging/ILogger.h"
#include "jurisdiction.hpp"
#include "date.h"
#include "betting_type/market_filter.h"

#include "response.h"
namespace BetfairAPI {
    class BetfairManager {
        public:
            BetfairManager(const std::string& username,
                const std::string& password,
                std::string api_key,
                Jurisdiction j = Jurisdiction::GLOBAL,
                std::unique_ptr<Logging::ILogger> logger = nullptr
            );
            ~BetfairManager();
            BetfairManager(const BetfairManager&) = delete;
            BetfairManager& operator=(const BetfairManager&) = delete;
            BetfairManager(BetfairManager&&) noexcept = delete;
            BetfairManager& operator=(BetfairManager&&) noexcept = delete;

            Response getEventTypes(const BettingType::MarketFilter& mf);

            bool refreshSession();
            
            
        private:
            bool endSession();

            std::string username_;
            std::string api_token_;//maybe need more secure storage in future
            std::string session_token_;
            Jurisdiction jurisdiction_;
            int refresh_time_;
            std::unique_ptr<Logging::ILogger> logger_;

            std::thread keep_alive_thread_;
            std::mutex mutex_;
            std::condition_variable cv_;
            std::atomic<bool> stop_thread_{false};

            void keepAliveLoop();

    };
}