#pragma once

#include <string>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <vector>

#include "Logging/ILogger.h"
#include "jurisdiction.hpp"
#include "date.h"
#include "betting_type/market_filter.h"
#include "betting_type/event_type_result.h"
#include "betting_type/time_range_result.h"
#include "betting_type/competition_result.h"
#include "betting_type/event_result.h"
#include "betting_enum/time_granularity.hpp"
#include "betting_type/market_type_result.h"
#include "betting_type/country_code_result.h"
#include "betting_type/venue_result.h"
#include "betting_type/market_catalogue.h"
#include "betting_enum/market_projection.hpp"
#include "betting_enum/market_sort.hpp"

#include "response.h"

//might want a locale str as member var
namespace BetfairAPI {
    class BetfairManager {
        public:
            BetfairManager(const std::string& username,
                const std::string& password,
                std::string api_key,
                Jurisdiction j = Jurisdiction::GLOBAL,
                std::string locale = "en",
                std::unique_ptr<Logging::ILogger> logger = nullptr
            );
            ~BetfairManager();
            BetfairManager(const BetfairManager&) = delete;
            BetfairManager& operator=(const BetfairManager&) = delete;
            BetfairManager(BetfairManager&&) noexcept = delete;
            BetfairManager& operator=(BetfairManager&&) noexcept = delete;

            std::vector<BettingType::EventTypeResult> getEventTypes(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::CompetitionResult> getCompetitions(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::TimeRangeResult> getTimeRanges(const BettingType::MarketFilter& mf = {},
                BettingEnum::TimeGranularity granularity = BettingEnum::TimeGranularity::DAYS
            );
            std::vector<BettingType::EventResult> getEvents(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::MarketTypeResult> getMarketTypeResults(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::CountryCodeResult> getCountries(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::VenueResult> getVenues(const BettingType::MarketFilter& mf = {});
            std::vector<BettingType::MarketCatalogue> getMarketCatalogues(const BettingType::MarketFilter& = {},
                const std::set<BettingEnum::MarketProjection>& market_projection = {},
                const std::set<BettingEnum::MarketSort>& market_sort = {},
                int maxResults = 1000
            );

            bool refreshSession();
            
            
        private:
            bool endSession();

            std::string username_;
            std::string api_token_;//maybe need more secure storage in future
            std::string session_token_;
            Jurisdiction jurisdiction_;
            std::string locale_;
            int refresh_time_;
            std::unique_ptr<Logging::ILogger> logger_;

            std::thread keep_alive_thread_;
            std::mutex mutex_;
            std::condition_variable cv_;
            std::atomic<bool> stop_thread_{false};

            void keepAliveLoop();
            void setLoggingFlags();
            //track log states
            bool is_debug_level_;
            bool is_info_level_;
            bool is_warn_level_;
            bool is_error_level_;
            bool is_critical_level_;
    };
}