#pragma once

#include <string>
#include "BetfairAPI/response.h"
#include "BetfairAPI/jurisdiction.hpp"

namespace BetfairAPI {

    //note that if api requests fail, the request body is automatically stored inside Response

    Response interactiveLogin(const std::string& apiKey,
        const std::string& username,
        const std::string& password,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response keepAlive(const std::string& apiKey,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );

    Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        bool save_request_info = false
    );
}