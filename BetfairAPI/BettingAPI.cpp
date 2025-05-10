#include "BettingAPI.h"

#include <cpr/cpr.h>

namespace BetfairAPI {
    const char* base_url = "https://api.betfair.com/exchange/betting/rest/v1.0/";

    Response listEventTypes(std::string application_token,std::string session_token) {
        cpr::Url url {std::string(base_url) + "listEventTypes/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = "";
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);

        return Response(r);
    }
}