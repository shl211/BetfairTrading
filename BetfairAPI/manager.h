#pragma once

#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>

#include "jurisdiction.hpp"
#include "date.h"

namespace BetfairAPI {
    class BetfairManager {
        public:
            BetfairManager(const std::string& username,
                const std::string& password,
                std::string api_key,
                Jurisdiction j = Jurisdiction::GLOBAL
            );
            ~BetfairManager();
            BetfairManager(const BetfairManager&) = delete;
            BetfairManager& operator=(const BetfairManager&) = delete;
            BetfairManager(BetfairManager&&) noexcept = delete;
            BetfairManager& operator=(BetfairManager&&) noexcept = delete;

            bool refreshSession();
            
        private:
            bool endSession();

            std::string api_token_;//maybe need more secure storage in future
            std::string session_token_;
            Jurisdiction jurisdiction_;
            int refresh_time_;

            std::thread keep_alive_thread_;
            std::mutex mutex_;
            std::condition_variable cv_;
            std::atomic<bool> stop_thread_{false};

            void keepAliveLoop();

    };
}