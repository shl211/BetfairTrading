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
#include "betting_type/time_range.h"
#include "betting_enum/market_projection.hpp"
#include "betting_enum/market_sort.hpp"
#include "betting_enum/order_projection.hpp"
#include "betting_enum/side.hpp"
#include "betting_enum/sort_dir.hpp"
#include "betting_enum/persistence_type.hpp"
#include "betting_enum/order_by.hpp"
#include "betting_enum/order_type.hpp"
#include "betting_enum/order_projection.hpp"
#include "betting_enum/match_projection.hpp"
#include "betting_enum/bet_status.hpp"
#include "betting_enum/group_by.hpp"
#include "betting_type/current_order_summary_report.h"
#include "betting_type/cleared_order_summary_report.h"
#include "betting_type/runner_id.h"
#include "betting_type/place_execution_report.h"
#include "betting_type/cancel_execution_report.h"
#include "betting_type/replace_execution_report.h"
#include "betting_type/replace_instruction.h"
#include "betting_type/update_execution_report.h"
#include "betting_type/market_book.h"
#include "betting_type/price_projection.h"

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
            std::vector<BettingType::CurrentOrderSummary> getCurrentOrders(
                const std::set<std::string> bet_ids = {},
                const std::set<std::string> market_ids = {},
                std::optional<BettingEnum::OrderProjection> order_projection = std::nullopt,
                const std::set<std::string> customer_order_refs = {},
                const std::set<std::string> customer_strategy_refs = {},
                std::optional<BettingType::TimeRange> date_range = std::nullopt,
                std::optional<BettingEnum::OrderBy> order_by = std::nullopt,
                std::optional<BettingEnum::SortDir> sort_die = std::nullopt,
                bool include_item_description = false,
                bool include_source_id = false
            );
            std::vector<BettingType::ClearedOrderSummary> getClearedOrders(
                BettingEnum::BetStatus bet_status = BettingEnum::BetStatus::SETTLED,
                std::optional<BettingType::TimeRange> settled_date_range = std::nullopt,
                const std::set<std::string>& event_type_ids = {},
                const std::set<std::string>& event_ids = {},
                const std::set<std::string>& market_ids = {},
                const std::set<BettingType::RunnerId>& runner_ids = {},
                const std::set<std::string> bet_ids = {},
                std::optional<BettingEnum::Side> side = std::nullopt,
                std::optional<BettingEnum::GroupBy> group_by = std::nullopt,
                bool include_item_description = false,
                bool include_source_id = false
            );
            BettingType::PlaceExecutionReport placeOrders(
                std::string market_id,
                const std::vector<BettingType::PlaceInstruction>& instructions,
                std::optional<BettingType::MarketVersion> market_version = std::nullopt,
                std::optional<std::string> customer_ref = std::nullopt,
                std::optional<std::string> customer_strategy_ref = std::nullopt,
                std::optional<bool> async = std::nullopt
            );
            BettingType::CancelExecutionReport cancelOrders(
                std::string market_id = "",
                const std::vector<BettingType::CancelInstruction>& instructions = {},
                std::optional<std::string> customer_ref = std::nullopt
            );
            BettingType::UpdateExecutionReport updateOrders(
                std::string market_id = "",
                const std::vector<BettingType::UpdateInstruction>& instructions = {},
                std::optional<std::string> customer_ref = std::nullopt
            );
            BettingType::ReplaceExecutionReport replaceOrders(
                std::string market_id = "",
                const std::vector<BettingType::ReplaceInstruction>& instructions = {},
                std::optional<BettingType::MarketVersion> market_version = std::nullopt,
                std::optional<std::string> customer_ref = std::nullopt,
                std::optional<bool> async = std::nullopt
            );
            std::vector<BettingType::MarketBook> getMarketBook(
                const std::vector<std::string>& market_ids,
                std::optional<BettingType::PriceProjection> price_projection = std::nullopt,
                std::optional<BettingEnum::OrderProjection> order_projection = std::nullopt,
                std::optional<BettingEnum::MatchProjection> match_projection = std::nullopt,
                std::optional<bool> include_overall_position = std::nullopt,
                std::optional<bool> partition_matched_by_strategy_ref = std::nullopt,
                std::set<std::string> customer_strategy_refs = {},
                std::optional<Date> matched_since = std::nullopt,
                std::set<std::string> bet_ids = {}
            );
            std::vector<BettingType::MarketBook> getRunnerBook(
                const std::string& market_id,
                long selection_id,
                std::optional<BettingType::PriceProjection> price_projection = std::nullopt,
                std::optional<BettingEnum::OrderProjection> order_projection = std::nullopt,
                std::optional<BettingEnum::MatchProjection> match_projection = std::nullopt,
                std::optional<bool> include_overall_position = std::nullopt,
                std::optional<bool> partition_matched_by_strategy_ref = std::nullopt,
                std::set<std::string> customer_strategy_refs = {},
                std::optional<Date> matched_since = std::nullopt,
                std::set<std::string> bet_ids = {}
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