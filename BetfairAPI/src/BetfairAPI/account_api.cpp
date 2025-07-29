#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "http/client.h"
#include "BetfairAPI/account_api.h"
#include "BetfairAPI/account_type/json_serialiser.hpp"
#include "BetfairAPI/utils.h"

namespace BetfairAPI {
    namespace {
        std::string_view global_url = "https://api.betfair.com/exchange/account/rest/v1.0/";
        std::string_view nz_url = "https://api.betfair.com.au/exchange/account/rest/v1.0/";
    
        constexpr std::string_view getUrl(Jurisdiction j) {
            return j == Jurisdiction::NEWZEALAND ? nz_url : global_url;
        }
    }

    HTTP::Response getAccountFunds(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<AccountEnum::Wallet> wallet,
        const Jurisdiction jurisdiction,
        std::shared_ptr<Logging::ILogger> logger
    ) {
        std::string url{std::string(getUrl(jurisdiction)) + "getAccountFunds/"};
        std::map<std::string,std::string> headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };
        nlohmann::json j;
        if(wallet) j["wallet"] = to_string(*wallet);

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),j.dump()};
        HTTP::HTTPClient client(logger);

        return client.makeRequest(std::move(request));
    }

    HTTP::Response getAccountDetails(
        const std::string& api_key,
        const std::string& session_key,
        const Jurisdiction jurisdiction,
        std::shared_ptr<Logging::ILogger> logger
    ) {
        std::string url{std::string(getUrl(jurisdiction)) + "getAccountDetails/"};
        std::map<std::string,std::string> headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),""};
        HTTP::HTTPClient client(logger);

        return client.makeRequest(std::move(request));
    }

    HTTP::Response getAccountStatement(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<std::string> locale,
        std::optional<int> from_record,
        std::optional<int> record_count,
        std::optional<AccountType::TimeRange> item_date_range,
        std::optional<AccountEnum::IncludeItem> include_item,
        const Jurisdiction jurisdiction,
        std::shared_ptr<Logging::ILogger> logger
    ) {
        std::string url{std::string(getUrl(jurisdiction)) + "getAccountStatement/"};
        std::map<std::string,std::string> headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        if(locale) j["locale"] = *locale;
        if(from_record) j["fromRecord"] = *from_record;
        if(record_count) j["recordCount"] = *record_count;
        if(item_date_range) j["itemDateRange"] = *item_date_range;
        if(include_item) j["includeItem"] = to_string(*include_item);

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),j.dump()};
        HTTP::HTTPClient client(logger);

        return client.makeRequest(std::move(request));
    }
}