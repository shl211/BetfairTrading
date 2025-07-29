#include <cpr/cpr.h>
#include "BetfairAPI/session_api.h"

namespace BetfairAPI {
    
    namespace {
        constexpr std::string_view login_path{"login/"}; 
        constexpr std::string_view keep_alive_path{"keepAlive/"};
        constexpr std::string_view logout_path{"logout/"};

        HTTP::Response toResponse(cpr::Response& r,
            bool saveRequestBody=false, 
            const std::string& url = "", 
            const nlohmann::json& requestBody = {}
        ) {
            
            //cpr Response will be made unsafe, but that is ok, as it should be discarded anyway
            HTTP::Response response(r.status_code,std::move(r.text));
            
            return response;
        }
    }

    HTTP::Response interactiveLogin(const std::string& api_key,
        const std::string& username,
        const std::string& password,
        Jurisdiction j,
        bool save_request_info
    ) {

        std::string url{std::string(getBetfairUrl(j)) + std::string(login_path)};
        cpr::Url login_url{url};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"Content-Type","application/x-www-form-urlencoded"}
        };

        cpr::Body body {"username=" + cpr::util::urlEncode(username) +
                "&password=" + cpr::util::urlEncode(password)};

        cpr::Response response = cpr::Post(login_url,headers,body);

        //don't reveal the actual body in this case if logged
        return toResponse(response,false,url,{"username=***&password=***"});
    }

    HTTP::Response keepAlive(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j,
        bool save_request_info
    ) {

        std::string url{std::string(getBetfairUrl(j)) + std::string(keep_alive_path)};
        cpr::Url keep_alive_url{url};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        cpr::Response response = cpr::Post(keep_alive_url,headers);
        return toResponse(response,save_request_info,url);
    }

    HTTP::Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j,
        bool save_request_info
    ) {

        std::string url{std::string(getBetfairUrl(j)) + std::string(logout_path)};
        cpr::Url logout_url{url};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        cpr::Response response = cpr::Post(logout_url,headers);
        return toResponse(response,save_request_info,url);
    }
}