#include <cpr/cpr.h>
#include "session.h"

namespace BetfairAPI {
    
    namespace {
        constexpr std::string_view login_path{"login/"}; 
        constexpr std::string_view keep_alive_path{"keepAlive/"};
        constexpr std::string_view logout_path{"logout/"};

        Response toResponse(cpr::Response& r) {
            //cpr Response will be made unsafe, but that is ok, as it should be discarded anyway
            return Response(r.status_code,std::move(r.text));
        }
    }

    Response interactiveLogin(const std::string& api_key,
        const std::string& username,
        const std::string& password,
        Jurisdiction j) {

        cpr::Url login_url{std::string(getBetfairUrl(j)) + std::string(login_path)};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"Content-Type","application/x-www-form-urlencoded"}
        };

        cpr::Body body {"username=" + cpr::util::urlEncode(username) +
                "&password=" + cpr::util::urlEncode(password)};

        cpr::Response response = cpr::Post(login_url,headers,body);
        return toResponse(response);
    }

    Response keepAlive(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j) {

        cpr::Url keep_alive_url{std::string(getBetfairUrl(j)) + std::string(keep_alive_path)};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        cpr::Response response = cpr::Post(keep_alive_url,headers);
        return toResponse(response);
    }

    Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j) {

        cpr::Url logout_url{std::string(getBetfairUrl(j)) + std::string(logout_path)};
        cpr::Header headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        cpr::Response response = cpr::Post(logout_url,headers);
        return toResponse(response);
    }
}