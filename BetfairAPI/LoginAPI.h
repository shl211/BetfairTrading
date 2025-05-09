#ifndef LOGIN_API_H
#define LOGIN_API_H

#include <cpr/cpr.h>
#include <string>
#include "Response.h"

namespace BetfairAPI {
    Response login(const std::string& apiKey,const std::string& username,const std::string& password);
}

#endif