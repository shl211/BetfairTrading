#ifndef BETTING_API_H
#define BETTING_API_H

#include <cpr/cpr.h>
#include "Response.h"

namespace BetfairAPI {

    Response listEventTypes(std::string application_token,std::string session_token);
}


#endif