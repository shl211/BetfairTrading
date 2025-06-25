#include "betting_api.h"
#include "betting_type_json_serialiser.h"
#include "utils/enum_utils.hpp"

#include <iostream>
namespace BetfairAPI {
    BetfairAPI::Utils::Response listEventTypes(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {
        
        cpr::Url url {std::string(betting_endpoint_url) + "listEventTypes/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter; 
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }

    BetfairAPI::Utils::Response listCompetitions(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {
        cpr::Url url {std::string(betting_endpoint_url) + "listCompetitions/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter;
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }

    BetfairAPI::Utils::Response listEvents(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {
        cpr::Url url {std::string(betting_endpoint_url) + "listEvents/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter;
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }
    
    BetfairAPI::Utils::Response listMarketTypes(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {
            cpr::Url url {std::string(betting_endpoint_url) + "listMarketTypes/"};
            cpr::Header headers {
                {"X-Application",application_token},
                {"X-Authentication",session_token},
                {"Content-Type","application/json"}
            };
        
            nlohmann::json j;
            j["filter"] = filter;
            cpr::Body body {j.dump()};
            
            cpr::Response r = cpr::Post(url,headers,body);
            return BetfairAPI::Utils::Response(r);
        }
        
        BetfairAPI::Utils::Response listTimeRanges(std::string application_token,std::string session_token,
            const BetfairAPI::BettingType::MarketFilter& filter, BettingEnum::TimeGranularity granularity) {
                
            cpr::Url url {std::string(betting_endpoint_url) + "listTimeRanges/"};
            cpr::Header headers {
                {"X-Application",application_token},
                {"X-Authentication",session_token},
                {"Content-Type","application/json"}
            };
        
            nlohmann::json j;
            j["filter"] = filter;
            j["granularity"] = Utils::to_string<BettingEnum::TimeGranularity>(granularity);
            cpr::Body body {j.dump()};
            
            cpr::Response r = cpr::Post(url,headers,body);
            return BetfairAPI::Utils::Response(r);
        }
}