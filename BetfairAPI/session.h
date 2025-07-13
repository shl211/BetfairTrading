#pragma once

#include <string>
#include "response.h"
#include "jurisdiction.hpp"

namespace BetfairAPI {

    Response interactiveLogin(const std::string& apiKey,
        const std::string& username,
        const std::string& password,
        Jurisdiction j = Jurisdiction::GLOBAL);

    Response keepAlive(const std::string& apiKey,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL);

    Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL);
}