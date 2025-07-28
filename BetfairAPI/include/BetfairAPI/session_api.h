#pragma once

#include <string>
#include "http/response.h"
#include "BetfairAPI/jurisdiction.hpp"

namespace BetfairAPI {

    //note that if api requests fail, the request body is automatically stored inside Response

    HTTP::Response interactiveLogin(const std::string& apiKey,
        const std::string& username,
        const std::string& password,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    HTTP::Response keepAlive(const std::string& apiKey,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    HTTP::Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
}