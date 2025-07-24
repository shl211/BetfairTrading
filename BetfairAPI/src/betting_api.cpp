#include <optional>
#include <cpr/cpr.h>
#include "BetfairAPI/utils.h"
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
            Response response(r.status_code,std::move(r.text),url);

            if(saveRequestBody || !response.isReponseOk()) {
                response.setRequestInfo(requestBody);
            }
            
            return response;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
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
        j["filter"] = mf;
        j["maxResults"] = max_results;

        if(locale != detail::default_locale) j["locale"] = locale;
        if(!market_sort.empty()) j["sort"] = to_string(market_sort);
        if(!market_projection.empty()) j["marketProjection"] = to_string(market_projection);

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
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listCurrentOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j {};

        if(!bet_ids.empty()) j["betIds"] = bet_ids;
        if(!market_ids.empty()) j["marketIds"] = market_ids;
        if(order_projection) j["orderProjection"] = *order_projection;
        if(!customer_order_refs.empty()) j["customerOrderRefs"] = customer_order_refs;
        if(!customter_strategy_refs.empty()) j["customerStrategyRefs"] = customter_strategy_refs;
        if(dateRange) j["dateRange"] = *dateRange;
        if(order_by) j["orderBy"] = *order_by;
        if(sort_dir) j["sortDir"] = *sort_dir;
        if(from_record >= 0) j["fromRecord"] = from_record;
        if(to_record >= 0 && to_record <= 1000) j["toRecord"] = to_record;
        if(include_item_description) j["includeItemDescription"] = *include_item_description;
        if(include_source_id) j["includeSourceId"] = *include_source_id;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listClearedOrders(const std::string& api_key,
        const std::string& session_key,
        BettingEnum::BetStatus bet_status,
        const std::set<std::string>& event_type_ids,
        const std::set<std::string>& event_ids,
        const std::set<std::string>& market_ids,
        const std::set<BettingType::RunnerId>& runner_ids,
        const std::set<std::string>bet_ids,
        std::optional<BettingEnum::Side> side,
        std::optional<BettingType::TimeRange> settled_date_range,
        std::optional<BettingEnum::GroupBy> group_by,
        std::optional<bool> include_item_description,
        std::optional<bool> include_source_id,
        std::string locale,
        int from_record,
        int record_count,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listClearedOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j {};
        j["betStatus"] = to_string<BettingEnum::BetStatus>(bet_status);
        if(!event_type_ids.empty()) j["eventTypeIds"] = event_type_ids;
        if(!event_ids.empty()) j["eventIds"] = event_ids;
        if(!market_ids.empty()) j["marketIds"] = market_ids;
        if(!runner_ids.empty()) j["runnerIds"] = runner_ids;
        if(!bet_ids.empty()) j["betIds"] = bet_ids;
        if(side) j["side"] = *side;
        if(settled_date_range) j["settledDateRange"] = (*settled_date_range);
        if(group_by) j["groupBy"] = *group_by;
        if(include_item_description) j["includeItemDescription"] = *include_item_description;
        if(include_source_id) j["includeSourceId"] = *include_source_id;
        if(locale != detail::default_locale) j["locale"] = locale;
        if(from_record != 0) j["fromRecord"] = 0;
        if(record_count != 0) j["recordCount"] = 1000;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    };

    Response placeOrders(const std::string& api_key,
        const std::string& session_key,
        std::string market_id,
        const std::vector<BettingType::PlaceInstruction>& instructions,
        std::optional<BettingType::MarketVersion> market_version,
        std::optional<std::string> customer_ref,
        std::optional<std::string> customer_strategy_ref,
        std::optional<bool> async,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {

        cpr::Url url{std::string(getUrl(jurisdiction)) + "placeOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j {};
        j["marketId"] = market_id;
        j["instructions"] = nlohmann::json::array();
        for (const auto& instr : instructions) {
            j["instructions"].push_back(instr);
        }
        if (market_version) j["marketVersion"] = *market_version;
        if (customer_ref) j["customerRef"] = *customer_ref;
        if (customer_strategy_ref) j["customerStrategyRef"] = *customer_strategy_ref;
        if (async) j["async"] = *async;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response cancelOrders(const std::string& api_key,
        const std::string& session_key,
        std::string market_id,
        const std::vector<BettingType::CancelInstruction>& instructions,
        std::optional<std::string> customer_ref,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "cancelOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key}
        };

        nlohmann::json j {};
        if(!market_id.empty()) j["marketId"] = market_id;
        j["instructions"] = instructions;
        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);  
    }

    Response updateOrders(const std::string& api_key,
        const std::string& session_key,
        std::string market_id,
        const std::vector<BettingType::UpdateInstruction>& instructions,
        std::optional<std::string> customer_ref,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "updateOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key}
        };

        nlohmann::json j {};
        if(!market_id.empty()) j["marketId"] = market_id;
        j["instructions"] = instructions;
        if (customer_ref) j["customerRef"] = *customer_ref;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }
    
    Response replaceOrders(const std::string& api_key,
        const std::string& session_key,
        std::string market_id,
        const std::vector<BettingType::ReplaceInstruction>& instructions,
        std::optional<BettingType::MarketVersion> market_version,
        std::optional<std::string> customer_ref,
        std::optional<bool> async,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "replaceOrders/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j {};
        j["marketId"] = market_id;
        j["instructions"] = instructions;
        if (market_version) j["marketVersion"] = *market_version;
        if (customer_ref) j["customerRef"] = *customer_ref;
        if (async) j["async"] = *async;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listMarketBook(const std::string& api_key,
        const std::string& session_key,
        const std::vector<std::string>& market_ids,
        std::optional<BettingType::PriceProjection> price_projection,
        std::optional<BettingEnum::OrderProjection> order_projection,
        std::optional<BettingEnum::MatchProjection> match_projection,
        std::optional<bool> include_overall_position,
        std::optional<bool> partition_matched_by_strategy_ref,
        std::set<std::string> customer_strategy_refs,
        std::optional<std::string> currency_code,
        std::optional<std::string> locale,
        std::optional<Date> matched_since,
        std::set<std::string> bet_ids,
        const Jurisdiction jurisdiction,
        bool save_request_info 
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listMarketBook/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key}
        };

        nlohmann::json j {};
        j["marketIds"] = market_ids;
        if(price_projection) j["priceProjection"] = *price_projection;
        if(order_projection) j["orderProjection"] = *order_projection;
        if(match_projection) j["matchProjection"] = *match_projection;
        if(include_overall_position) j["includeOverallPosition"] = *include_overall_position;
        if(partition_matched_by_strategy_ref) j["partitionMatchedByStrategyRef"] = *partition_matched_by_strategy_ref;
        if(!customer_strategy_refs.empty()) j["customerStrategyRefs"] = customer_strategy_refs;
        if(currency_code) j["currencyCode"] = *currency_code;
        if(locale) j["locale"] = *locale;
        if(matched_since) j["matchedSince"] = matched_since->getIsoString();
        if(!bet_ids.empty()) j["betIds"] = bet_ids;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listRunnerBook(const std::string& api_key,
        const std::string& session_key,
        const std::string& market_id,
        long selection_id,
        std::optional<BettingType::PriceProjection> price_projection,
        std::optional<BettingEnum::OrderProjection> order_projection,
        std::optional<BettingEnum::MatchProjection> match_projection,
        std::optional<bool> include_overall_position,
        std::optional<bool> partition_matched_by_strategy_ref,
        std::set<std::string> customer_strategy_refs,
        std::optional<std::string> currency_code,
        std::optional<std::string> locale,
        std::optional<Date> matched_since,
        std::set<std::string> bet_ids,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listRunnerBook/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key}
        };

        nlohmann::json j {};
        j["marketId"] = market_id;
        j["selectionId"] = selection_id;
        if(price_projection) j["priceProjection"] = *price_projection;
        if(order_projection) j["orderProjection"] = *order_projection;
        if(match_projection) j["matchProjection"] = *match_projection;
        if(include_overall_position) j["includeOverallPosition"] = *include_overall_position;
        if(partition_matched_by_strategy_ref) j["partitionMatchedByStrategyRef"] = *partition_matched_by_strategy_ref;
        if(!customer_strategy_refs.empty()) j["customerStrategyRefs"] = customer_strategy_refs;
        if(currency_code) j["currencyCode"] = *currency_code;
        if(locale) j["locale"] = *locale;
        if(matched_since) j["matchedSince"] = matched_since->getIsoString();
        if(!bet_ids.empty()) j["betIds"] = bet_ids;

        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }

    Response listMarketProfitAndLoss(const std::string& api_key,
        const std::string& session_key,
        const std::set<std::string>& market_ids,
        std::optional<bool> include_settled_bets,
        std::optional<bool> include_bsp_bets,
        std::optional<bool> net_of_commission,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {        
        cpr::Url url{std::string(getUrl(jurisdiction)) + "listMarketProfitAndLoss/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key}
        };

        nlohmann::json j {};
        j["marketIds"] = market_ids;
        if(include_settled_bets) j["includeSettledBets"] = *include_settled_bets;
        if(include_bsp_bets) j["includeBspBets"] = *include_bsp_bets;
        if(net_of_commission) j["netOfCommission"] = *net_of_commission;
        
        cpr::Body body{j.dump()};
        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }
}