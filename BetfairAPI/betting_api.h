#pragma once

#include <string>
#include <vector>
#include "betting_type/market_filter.h"
#include "utils/response.h"
#include "betting_enum/time_granularity.hpp"
#include "betting_enum/market_projection.hpp"
#include "betting_enum/market_sort.hpp"
#include "betting_type/price_projection.h"
#include "order_projection.hpp"
#include "match_projection.hpp"
#include "betting_enum/order_by.hpp"
#include "betting_enum/sort_dir.hpp"

namespace BetfairAPI {

    static const char* betting_endpoint_url{"https://api.betfair.com/exchange/betting/rest/v1.0/"};

    BetfairAPI::Utils::Response listEventTypes(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");

    BetfairAPI::Utils::Response listCompetitions(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");
    
    BetfairAPI::Utils::Response listEvents(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");

    BetfairAPI::Utils::Response listMarketTypes(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");
        
    BetfairAPI::Utils::Response listTimeRanges(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, BettingEnum::TimeGranularity granularity);

    BetfairAPI::Utils::Response listCountries(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");

    BetfairAPI::Utils::Response listVenues(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");

    Utils::Response listMarketCatalogue(std::string application_token,std::string session_token,
        const BettingType::MarketFilter& filter, const std::vector<BettingEnum::MarketProjection>& market_projection = {},
        BettingEnum::MarketSort sort=BettingEnum::MarketSort::UNKNOWN, int max_results=1000, const std::string& locale = "en");

    Utils::Response listMarketBook(std::string application_token,std::string session_token,
        const std::vector<std::string>& market_ids,
        BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
        bool include_overall_position,bool position_matched_by_strategy_ref,
        std::vector<std::string> customer_strategy_refs,std::string currency_code,
        std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id);

    Utils::Response listMarketBook(std::string application_token,std::string session_token,
        const std::vector<std::string>& market_ids, const BettingType::PriceProjection& price_projection,
        BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
        bool include_overall_position,bool position_matched_by_strategy_ref,
        std::vector<std::string> customer_strategy_refs,std::string currency_code,
        std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id);

    Utils::Response listMarketProfitAndLoss(std::string application_token,std::string session_token,
        const std::vector<std::string>& market_ids,bool include_settled_bets,
        bool include_bsp_bets,bool net_of_commission);

    Utils::Response listCurrentOrders(std::string application_token,std::string session_token,
        const std::vector<std::string>& bet_ids, const std::vector<std::string>& market_ids,
        BettingEnum::OrderProjection order_projection,
        const BettingType::TimeRange& placed_date_range, BettingEnum::OrderBy order_by, 
        BettingEnum::SortDir sort_dir, int from_record, int record_count,
        bool include_item_desc, bool include_source_id,
        const std::vector<std::string>& customer_order_refs,
        const std::vector<std::string>& customer_strategy_ref);

}