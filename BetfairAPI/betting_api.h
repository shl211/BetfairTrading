#pragma once

#include <string>
#include <vector>
#include "betting_type/market_filter.h"
#include "utils/response.h"

namespace BetfairAPI {

    static const char* betting_endpoint_url{"https://api.betfair.com/exchange/betting/rest/v1.0/"};

    BetfairAPI::Utils::Response listEventTypes(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");

    BetfairAPI::Utils::Response listCompetitions(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale="en");
}