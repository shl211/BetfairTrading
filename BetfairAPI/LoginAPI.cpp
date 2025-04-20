#include "LoginAPI.h"

namespace BetfairAPI {
    
    const std::string URL = "https://identitysso.betfair.com/api/login";
    const cpr::Url LOGIN_URL{URL};
    
    cpr::Response login(const std::string& apiKey, const std::string& username,const std::string& password) {
        
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",apiKey},
            {"Content-Type","application/x-www-form-urlencoded"}
        };
        cpr::Body body {"username=" + username + "&password=" + password};
        
        return cpr::Post(LOGIN_URL,headers,body);
    };

}