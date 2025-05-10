#include "AccountAPI.h"

namespace BetfairAPI {
    const char* base_account_url = "https://api.betfair.com/exchange/account/rest/v1.0/";
    
    Response getAccountFunds(std::string application_token,std::string session_token,Wallet wallet) {
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["wallet"] = walletToString(wallet);
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(
            cpr::Url{std::string(base_account_url) + "getAccountFunds/"},
            headers,body
        );

        return Response(r);
    }
}