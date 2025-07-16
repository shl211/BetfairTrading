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

        Response toResponse(cpr::Response& r) {
            //cpr Response will be made unsafe, but that is ok, as it should be discarded anyway
            return Response(r.status_code,std::move(r.text));
        }

        template<typename Enum>
        std::string to_string(Enum value) {
            return std::string(magic_enum::enum_name(value));
        };
    }

    Response listEventTypes(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction
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
        return toResponse(response);
    }

    Response listCompetitions(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const std::string& locale,
        const Jurisdiction jurisdiction
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
        return toResponse(response);
    }
    
    Response listTimeRanges(const std::string& api_key,
        const std::string& session_key,
        const BettingType::MarketFilter& mf,
        const BettingEnum::TimeGranularity granularity,
        const Jurisdiction jurisdiction
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
        return toResponse(response);
    }
}