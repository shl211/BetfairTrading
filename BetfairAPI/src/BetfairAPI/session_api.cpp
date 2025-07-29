#include <cpr/cpr.h>
#include "BetfairAPI/session_api.h"

namespace BetfairAPI {
    
    namespace {
        constexpr std::string_view login_path{"login/"}; 
        constexpr std::string_view keep_alive_path{"keepAlive/"};
        constexpr std::string_view logout_path{"logout/"};
    }

    HTTP::Response interactiveLogin(const std::string& api_key,
        const std::string& username,
        const std::string& password,
        Jurisdiction j,
        std::shared_ptr<Logging::ILogger> logger
    ) {
        std::string url{std::string(getBetfairUrl(j)) + std::string(login_path)};
        std::map<std::string,std::string> headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"Content-Type","application/x-www-form-urlencoded"}
        };
        std::string body {"username=" + cpr::util::urlEncode(username) +
                "&password=" + cpr::util::urlEncode(password)};

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),std::move(body)};
        HTTP::HTTPClient client{logger};

        return client.makeRequest(request);
    }

    HTTP::Response keepAlive(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j,
        std::shared_ptr<Logging::ILogger> logger
    ) {
        std::string url{std::string(getBetfairUrl(j)) + std::string(keep_alive_path)};
        std::map<std::string,std::string> headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),""};
        HTTP::HTTPClient client{logger};

        return client.makeRequest(request);
    }

    HTTP::Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j,
        std::shared_ptr<Logging::ILogger> logger 
    ) {
        std::string url{std::string(getBetfairUrl(j)) + std::string(logout_path)};
        std::map<std::string,std::string> headers {
            {"Accept","application/json"},
            {"X-Application",api_key},
            {"X-Authentication",session_token},
        };

        HTTP::Request request{HTTP::Request::POST,std::move(url),std::move(headers),""};
        HTTP::HTTPClient client{logger};

        return client.makeRequest(request);
    }
}