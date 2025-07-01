#ifndef BETFAIR_MANAGER_H
#define BETFAIR_MANAGER_H

#include <nlohmann/json.hpp>
#include "betting_type/market_filter.h"
#include "betting_type/event_type_results.h"
#include "betting_type/competition_result.h"
#include "betting_type/event_result.h"
#include "betting_type/market_type_result.h"
#include "betting_type/time_range_result.h"
#include "betting_type/country_code_result.h"
#include "betting_enum/time_granularity.hpp"
#include "betting_type/venue_result.h"
#include "betting_type/market_catalogue.h"
#include "betting_enum/market_sort.hpp"
#include "betting_enum/market_projection.hpp"
#include "betting_type/market_book.h"
#include "betting_type/price_projection.h"
#include "betting_enum/order_projection.hpp"
#include "betting_enum/match_projection.hpp"
#include "betting_enum/order_by.hpp"
#include "betting_enum/sort_dir.hpp"
#include "betting_enum/bet_status.hpp"
#include "betting_enum/group_by.hpp"
#include "betting_type/market_profit_loss.h"
#include "betting_type/current_order_summary_report.h"
#include "betting_type/cleared_order_summary_report.h"

namespace BetfairAPI {
    class BetfairManager {
    
    public:
        BetfairManager(std::string username, std::string password, std::string api_key);
        BetfairManager(const BetfairManager&) = delete;
        BetfairManager(BetfairManager&& other) noexcept;
        BetfairManager& operator=(const BetfairManager&) = delete;
        BetfairManager& operator=(BetfairManager&&) noexcept;
        ~BetfairManager();
    
        double getAccountBalance() const;
        std::vector<BettingType::EventTypeResults> listEventTypes(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::CompetitionResult> listCompetitions(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::EventResult> listEvents(const BettingType::MarketFilter& mf,const std::string& locale="en") const;
        std::vector<BettingType::MarketTypeResult> listMarketTypes(const BettingType::MarketFilter& mf, const std::string& locale="en") const;
        std::vector<BettingType::TimeRangeResult> listTimeRanges(const BettingType::MarketFilter& mf, BettingEnum::TimeGranularity granularity) const;
        std::vector<BettingType::CountryCodeResult> listCountries(const BettingType::MarketFilter& mf, const std::string& locale="en") const;
        std::vector<BettingType::VenueResult> listVenues(const BettingType::MarketFilter& mf, const std::string& locale="en") const;
        std::vector<BettingType::MarketCatalogue> listMarketCatalogue(const BettingType::MarketFilter& filter, 
            const std::vector<BettingEnum::MarketProjection>& market_projection = {}, BettingEnum::MarketSort sort=BettingEnum::MarketSort::UNKNOWN, 
            int max_results=1000, const std::string& locale="en");
        
        std::vector<BettingType::MarketBook> listMarketBook(
            const std::vector<std::string>& market_ids,
            BettingEnum::OrderProjection order_projection = BettingEnum::OrderProjection::UNKNOWN,
            BettingEnum::MatchProjection match_projection = BettingEnum::MatchProjection::UNKNOWN,
            bool include_overall_position = true,bool position_matched_by_strategy_ref = false,
            const std::vector<std::string>& customer_strategy_refs = {},const std::string& currency_code = "GBP",
            const std::string& locale = "en", const Utils::Date& matched_since = Utils::Date(),
            const std::vector<std::string>& bet_id = {}
        );
        
        std::vector<BettingType::MarketBook> listMarketBook(
            const std::vector<std::string>& market_ids, const BettingType::PriceProjection& price_projection,
            BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
            bool include_overall_position,bool position_matched_by_strategy_ref,
            std::vector<std::string> customer_strategy_refs,std::string currency_code,
            std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id
        );

        std::vector<BettingType::MarketProfitLoss> listMarketProfitAndLoss(const std::vector<std::string>& market_ids,
            bool include_settled_bets=false,bool include_bsp_bets=false,bool net_of_commission=false);

        BettingType::CurrentOrderSummaryReport listCurrentOrders(
            const std::vector<std::string>& bet_ids = {}, 
            const std::vector<std::string>& market_ids = {},
            const BettingType::TimeRange& placed_date_range = {},
            BettingEnum::OrderProjection order_projection = BettingEnum::OrderProjection::UNKNOWN,
            BettingEnum::OrderBy order_by = BettingEnum::OrderBy::UNKNOWN,
            BettingEnum::SortDir sort_dir = BettingEnum::SortDir::UNKNOWN,
            int from_record = 0,
            int record_count = 0, //0 for get all up to limit
            bool include_item_desc = false,
            bool include_source_id = false,
            const std::vector<std::string>& customer_order_refs = {},
            const std::vector<std::string>& customer_strategy_ref = {}
        );

        BettingType::ClearedOrderSummaryReport listClearedOrders (
            BettingEnum::BetStatus bet_status = BettingEnum::BetStatus::UNKNOWN,
            const std::vector<BettingType::EventType>& event_types = {},
            const std::vector<BettingType::Event>& events = {},
            const std::vector<BettingType::MarketTypeResult>& market_types = {},
            const std::vector<BettingType::Runner>& runners = {},
            const std::vector<std::string>& bet_ids = {},
            BettingEnum::Side side = BettingEnum::Side::UNKNOWN,
            const BettingType::TimeRange& settled_date_range = {},
            BettingEnum::GroupBy group_by = BettingEnum::GroupBy::UNKNOWN,
            int from_record = 0,
            int record_count = 0, //0 for get all up to limit
            bool include_item_desc = false,
            bool include_source_id = false,
            const std::vector<std::string>& customer_order_refs = {},
            const std::vector<std::string>& customer_strategy_ref = {},
            const std::string& locale = "en"
        );

    private:
        std::string session_token_;
        std::string application_token_;
    
        double balance_;
        double discount_rate_;
        double exposure_;
        double exposure_limit_;
    
        void assignAccountInformation(const nlohmann::json& account_balance_response);
    };
}

#endif