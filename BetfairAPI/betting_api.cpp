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

        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }
    
    Utils::Response listMarketBook(std::string application_token,std::string session_token,
        const std::vector<std::string>& market_ids, const BettingType::PriceProjection& price_projection,
        BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
        bool include_overall_position,bool partition_matched_by_strategy_ref,
        std::vector<std::string> customer_strategy_refs,std::string currency_code,
        std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id) {

        std::cerr << "This is still under development and there may be bugs with price projection \n";
        
        cpr::Url url {std::string(betting_endpoint_url) + "listMarketBook/"};
        cpr::Header headers {
        {"X-Application",application_token},
        {"X-Authentication",session_token},
        {"Content-Type","application/json"}
        };
        
        nlohmann::json j;
        j["marketIds"] = market_ids;
        
        //if(!price_projection.getPriceData().empty()) {
        //    j["priceProjection"] = price_projection; //TODO -> to_json method
        //}
        
        if(order_projection != BettingEnum::OrderProjection::UNKNOWN) {
            j["orderProjection"] = Utils::to_string<BettingEnum::OrderProjection>(order_projection);

            //these only populated if orders are requested
            if(match_projection != BettingEnum::MatchProjection::UNKNOWN) {
                j["matchProjection"] = Utils::to_string<BettingEnum::MatchProjection>(match_projection);
            }

            j["includeOverallPosition"] = include_overall_position;
            j["partitionMatchedByStrategyRef"] = partition_matched_by_strategy_ref;
            j["customerStrategyRefs"] = customer_strategy_refs;
            
            if (matched_since.isValid()) {
                j["matchedDate"] = matched_since.toIsoString();
            }

            if(!bet_id.empty()) {
                j["betIds"] = bet_id;//TODO this should be max 250???
            }
        }

        j["currencyCode"] = currency_code;  
        j["locale"] = locale;

        std::cerr << j << "\n";
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);
    }

    Utils::Response listMarketBook(std::string application_token,std::string session_token,
        const std::vector<std::string>& market_ids,
        BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
        bool include_overall_position,bool partition_matched_by_strategy_ref,
        std::vector<std::string> customer_strategy_refs,std::string currency_code,
        std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id) {

        cpr::Url url {std::string(betting_endpoint_url) + "listMarketBook/"};
        cpr::Header headers {
        {"X-Application",application_token},
        {"X-Authentication",session_token},
        {"Content-Type","application/json"}
        };
        
        nlohmann::json j;
        j["marketIds"] = market_ids;
        
        if(order_projection != BettingEnum::OrderProjection::UNKNOWN) {
            j["orderProjection"] = Utils::to_string<BettingEnum::OrderProjection>(order_projection);

            //these only populated if orders are requested
            if(match_projection != BettingEnum::MatchProjection::UNKNOWN) {
                j["matchProjection"] = Utils::to_string<BettingEnum::MatchProjection>(match_projection);
            }

            j["includeOverallPosition"] = include_overall_position;
            j["partitionMatchedByStrategyRef"] = partition_matched_by_strategy_ref;
            j["customerStrategyRefs"] = customer_strategy_refs;
            
            if (matched_since.isValid()) {
                j["matchedDate"] = matched_since.toIsoString();
            }

            if(!bet_id.empty()) {
                j["betIds"] = bet_id;//TODO this should be max 250???
            }
        }

        j["currencyCode"] = currency_code;  
        j["locale"] = locale;

        std::cerr << j << "\n";
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(url,headers,body);
        return BetfairAPI::Utils::Response(r);

    }
}