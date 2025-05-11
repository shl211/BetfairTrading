#ifndef BETTING_API_H
#define BETTING_API_H

#include <cpr/cpr.h>
#include "Response.h"
#include "MarketFilter.h"
#include "TimeGranularity.hpp"

namespace BetfairAPI {

    Response listEventTypes(std::string application_token,std::string session_token,
                            const MarketFilter& filter = {});

    Response listCompetitions(std::string application_token,std::string session_token,
                            const MarketFilter& filter = {});

    Response listTimeRanges(std::string application_token,std::string session_token,
                            const MarketFilter& filter = {},const TimeGranularity& granularity = TimeGranularity::DAYS);
}


#endif