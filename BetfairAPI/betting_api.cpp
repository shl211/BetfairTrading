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
    
    BetfairAPI::Utils::Response listCountries(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {
        
        cpr::Url url {std::string(betting_endpoint_url) + "listCountries/"};
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

    BetfairAPI::Utils::Response listVenues(std::string application_token,std::string session_token,
        const BetfairAPI::BettingType::MarketFilter& filter, std::string_view locale) {

        cpr::Url url {std::string(betting_endpoint_url) + "listVenues/"};
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
    
    Utils::Response listMarketCatalogue(std::string application_token,std::string session_token,
        const BettingType::MarketFilter& filter, const std::vector<BettingEnum::MarketProjection>& market_projection,
        BettingEnum::MarketSort sort, int max_results, const std::string& locale) {
                
        std::cerr << "This is still under development and there may be bugs \n";

        cpr::Url url {std::string(betting_endpoint_url) + "listMarketCatalogue/"};
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["filter"] = filter;

        if (!market_projection.empty()) {
            j["marketProjection"] = Utils::to_string<BettingEnum::MarketProjection>(market_projection);
        }

        if(sort != BettingEnum::MarketSort::UNKNOWN) {
            j["sort"] = Utils::to_string<BettingEnum::MarketSort>(sort);
        }
        
        //max_results must be in range 0 and 1000
        if (max_results > 1000) {
            std::cerr << "Requested " << max_results << " results, but the API allows a maximum of 1000. Trimming to 1000.";
            max_results = 1000;
        }
        if(max_results <= 0) {
            std::cerr << "Requested " << max_results << " results, but the API allows a minimum of 1. Trimming to 1.";
            max_results = 1;
        }
        j["maxResults"] = max_results;
        

        j["locale"] = locale;

        std::cerr << j << "\n";
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }
}