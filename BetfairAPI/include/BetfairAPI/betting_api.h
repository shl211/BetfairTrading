#pragma once

#include <string>
#include <set>
#include "response.h"
#include "jurisdiction.hpp"
#include "betting_type/market_filter.h"
#include "betting_enum/time_granularity.hpp"
#include "betting_enum/market_projection.hpp"
#include "betting_enum/market_sort.hpp"
#include "betting_enum/order_projection.hpp"
#include "betting_enum/order_by.hpp"
#include "betting_enum/sort_dir.hpp"
namespace BetfairAPI {
    //note that if api requests fail, the request body is automatically stored inside Response

    namespace detail {
        inline std::string default_locale = "en";
    }

    Response listEventTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listCompetitions(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listTimeRanges(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const BettingEnum::TimeGranularity granularity,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listEvents(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listMarketTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listCountries(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
    
    Response listVenues(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listMarketCatalogue(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::set<BettingEnum::MarketProjection>& market_projection = {},
        const std::set<BettingEnum::MarketSort>& market_sort = {},
        int max_results = 1000, 
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response listCurrentOrders(const std::string& api_key,
        const std::string& session_key,
        const std::set<std::string>& bet_ids = {},
        const std::set<std::string>& market_ids = {},
        std::optional<BettingEnum::OrderProjection> order_projection = std::nullopt,
        const std::set<std::string>& customer_order_refs = {},
        const std::set<std::string>& customter_strategy_refs = {},
        std::optional<BettingType::TimeRange> dateRange = std::nullopt,
        std::optional<BettingEnum::OrderBy> order_by = std::nullopt,
        std::optional<BettingEnum::SortDir> sort_dir = std::nullopt,
        int from_record = 0,
        int to_record = 1000,
        std::optional<bool> include_item_description = std::nullopt,
        std::optional<bool> include_source_id = std::nullopt,
        const Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
}