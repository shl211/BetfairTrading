#include "BettingAPI.h"

#include <cpr/cpr.h>

namespace BetfairAPI {
    const char* base_betting_url = "https://api.betfair.com/exchange/betting/rest/v1.0/";

    Response listEventTypes(std::string application_token,std::string session_token,
                        const MarketFilter& filter) {
        
        cpr::Url url {std::string(base_betting_url) + "listEventTypes/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter.getFilterJson();
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return Response(r);
    }

    Response listCompetitions(std::string application_token,std::string session_token,
                            const MarketFilter& filter) {
        
        cpr::Url url {std::string(base_betting_url) + "listCompetitions/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter.getFilterJson();
        cpr::Body body {j.dump()};

        cpr::Response r = cpr::Post(url,headers,body);
        return Response(r);
    }

    Response listTimeRanges(std::string application_token,std::string session_token,
                            const MarketFilter& filter,const TimeGranularity& granularity) {
        
        cpr::Url url {std::string(base_betting_url) + "listTimeRanges/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter.getFilterJson();
        j["granularity"] = std::string(BetfairAPI::timeGranularityToString(granularity));
        cpr::Body body {j.dump()};

        cpr::Response r = cpr::Post(url,headers,body);
        return Response(r);
    }
}