#include <optional>
#include <magic_enum.hpp>
#include <cpr/cpr.h>
#include "BetfairAPI/betting_api.h"
#include "BetfairAPI/betting_type/json_serialiser.hpp"

namespace BetfairAPI {
    
    namespace {
        std::string_view global_url = "https://api.betfair.com/exchange/betting/rest/v1.0/";
        std::string_view nz_url = "https://api.betfair.com.au/exchange/betting/rest/v1.0/";
    
        constexpr std::string_view getUrl(Jurisdiction j) {
            return j == Jurisdiction::NEWZEALAND ? nz_url : global_url;
        }

        Response toResponse(cpr::Response& r,
            bool saveRequestBody=false, 
            const std::string& url = "", 
            const nlohmann::json& requestBody = {}
        ) {
            
            //cpr Response will be made unsafe, but that is ok, as it should be discarded anyway
            Response response(r.status_code,std::move(r.text));

            if(saveRequestBody || !response.isReponseOk()) {
                response.setRequestInfo(url,requestBody);
            }
            
            return response;
        };

        template<typename Enum>
        std::string to_string(Enum value) {
            return std::string(magic_enum::enum_name(value));
        };

        template<typename Enum>
        std::set<std::string> to_string(std::set<Enum> value) {
            std::set<std::string> res;            
            for(auto& v : value) {
                res.insert(to_string<Enum>(v));
            }
            return res;
        };
    }

    Response listEventTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {

        cpr::Url url{std::string(getUrl(jurisdiction)) + "listEventTypes/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listCompetitions(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listCompetitions/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }
    
    Response listTimeRanges(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const BettingEnum::TimeGranularity granularity,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listTimeRanges/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        j["granularity"] = to_string<BetfairAPI::BettingEnum::TimeGranularity>(granularity);

        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listEvents(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {

        cpr::Url url{std::string(getUrl(jurisdiction)) + "listEvents/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listMarketTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listMarketTypes/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listCountries(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listCountries/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listVenues(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listVenues/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        if(locale != detail::default_locale) {
            j["locale"] = locale;
        }
        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listMarketCatalogue(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::set<BettingEnum::MarketProjection>& market_projection,
        const std::set<BettingEnum::MarketSort>& market_sort,
        int max_results, 
        const std::string& locale,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listMarketCatalogue/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        j["filter"] = BetfairAPI::BettingType::toJson(mf);
        j["maxResults"] = max_results;

        if(locale != detail::default_locale) j["locale"] = locale;
        if(!market_sort.empty()) j["sort"] = to_string<BettingEnum::MarketSort>(market_sort);
        if(!market_projection.empty()) j["marketProjection"] = to_string<BettingEnum::MarketProjection>(market_projection);

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listCurrentOrders(const std::string& api_key,
        const std::string& session_key,
        const std::set<std::string>& bet_ids,
        const std::set<std::string>& market_ids,
        std::optional<BettingEnum::OrderProjection> order_projection,
        const std::set<std::string>& customer_order_refs,
        const std::set<std::string>& customter_strategy_refs,
        std::optional<BettingType::TimeRange> dateRange,
        std::optional<BettingEnum::OrderBy> order_by,
        std::optional<BettingEnum::SortDir> sort_dir,
        int from_record,
        int to_record,
        std::optional<bool> include_item_description,
        std::optional<bool> include_source_id,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listMarketCatalogue/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j {};

        if(!bet_ids.empty()) j["betIds"] = bet_ids;
        if(!market_ids.empty()) j["marketIds"] = market_ids;
        if(order_projection) j["orderProjection"] = to_string<BettingEnum::OrderProjection>(*order_projection);
        if(!customer_order_refs.empty()) j["customerOrderRefs"] = customer_order_refs;
        if(!customter_strategy_refs.empty()) j["customerStrategyRefs"] = customter_strategy_refs;
        if(dateRange) j["dateRange"] = BettingType::toJson<BettingType::TimeRange>(*dateRange);
        if(order_by) j["orderBy"] = to_string<BettingEnum::OrderBy>(*order_by);
        if(sort_dir) j["sortDir"] = to_string<BettingEnum::SortDir>(*sort_dir);
        if(from_record >= 0) j["fromRecord"] = from_record;
        if(to_record >= 0 && to_record <= 1000) j["toRecord"] = to_record;
        if(include_item_description) j["includeItemDescription"] = *include_item_description;
        if(include_source_id) j["includeSourceId"] = *include_source_id;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }
}