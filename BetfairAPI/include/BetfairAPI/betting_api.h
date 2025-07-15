#pragma once

#include <string>
#include "response.h"
#include "jurisdiction.hpp"
#include "betting_type/market_filter.h"

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
}