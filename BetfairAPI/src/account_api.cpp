#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "BetfairAPI/account_api.h"
#include "BetfairAPI/utils.h"

namespace BetfairAPI {
    namespace {
        std::string_view global_url = "https://api.betfair.com/exchange/account/rest/v1.0/";
        std::string_view nz_url = "https://api.betfair.com.au/exchange/account/rest/v1.0/";
    
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


    Response getAccountFunds(
        const std::string& api_key,
        const std::string& session_key,
        std::optional<AccountEnum::Wallet> wallet,
        const Jurisdiction jurisdiction,
        bool save_request_info
    ) {
        cpr::Url url{std::string(getUrl(jurisdiction)) + "getAccountFunds/"};
        cpr::Header headers {
            {"Content-Type","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_key},
        };

        nlohmann::json j;
        if(wallet) j["wallet"] = to_string(*wallet);

        cpr::Body body{j.dump()};

        cpr::Response response = cpr::Post(url,headers,body);
        return toResponse(response,save_request_info,url.str(),j);
    }
}