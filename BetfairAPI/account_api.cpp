#include "account_api.h"

namespace BetfairAPI {
    static const char* base_url = "https://api.betfair.com/exchange/account/rest/v1.0/";
    
    BetfairAPI::Utils::Response getAccountFunds(std::string application_token,std::string session_token,Wallet wallet) {
        cpr::Header headers {
            {"X-Application",application_token},
            {"X-Authentication",session_token},
            {"Content-Type","application/json"}
        };

        nlohmann::json j;
        j["wallet"] = walletToString(wallet);
        cpr::Body body {j.dump()};
        
        cpr::Response r = cpr::Post(
            cpr::Url{std::string(base_url) + "getAccountFunds/"},
            headers,body
        );

        return BetfairAPI::Utils::Response(r);
    }
}