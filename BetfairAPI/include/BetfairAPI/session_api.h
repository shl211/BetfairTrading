#pragma once

#include <string>
#include "http/response.h"
#include "http/client.h"
#include "Logging/ILogger.h"
#include "BetfairAPI/jurisdiction.hpp"

namespace BetfairAPI {
    HTTP::Response interactiveLogin(const std::string& apiKey,
        const std::string& username,
        const std::string& password,
        Jurisdiction j = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );

    HTTP::Response keepAlive(const std::string& apiKey,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );

    HTTP::Response logout(const std::string& api_key,
        const std::string& session_token,
        Jurisdiction j = Jurisdiction::GLOBAL,
        std::shared_ptr<Logging::ILogger> logger = nullptr
    );
}