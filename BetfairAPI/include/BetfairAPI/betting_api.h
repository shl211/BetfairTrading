#pragma once

#include <string>
#include <set>
#include "response.h"
#include "jurisdiction.hpp"
#include "betting_type/market_filter.h"
#include "betting_enum/time_granularity.hpp"
#include "betting_enum/market_projection.hpp"
#include "betting_enum/market_sort.hpp"
namespace BetfairAPI {
    
    namespace detail {
        inline std::string default_locale = "en";
    }

    Response listEventTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listCompetitions(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listTimeRanges(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const BettingEnum::TimeGranularity granularity,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listEvents(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listMarketTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listCountries(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );
    
    Response listVenues(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

    Response listMarketCatalogue(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::set<BettingEnum::MarketProjection>& market_projection = {},
        const std::set<BettingEnum::MarketSort>& market_sort = {},
        int max_results = 1000, 
        const std::string& locale = detail::default_locale,
        const Jurisdiction j = Jurisdiction::GLOBAL
    );

}