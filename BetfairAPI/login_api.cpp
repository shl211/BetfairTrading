#include "login_api.h"

namespace BetfairAPI {
    
    const std::string URL = "https://identitysso.betfair.com/api/login";
    const cpr::Url LOGIN_URL{URL};
    
    BetfairAPI::Utils::Response login(const std::string& apiKey, const std::string& username,const std::string& password) {
        
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",apiKey},
            {"Content-Type","application/x-www-form-urlencoded"}
        };
        cpr::Body body {"username=" + cpr::util::urlEncode(username) + 
                        "&password=" + cpr::util::urlEncode(password)};
        
        cpr::Response response = cpr::Post(LOGIN_URL,headers,body);
        return BetfairAPI::Utils::Response(std::move(response));
    };
}