#include "http/request.h"

namespace BetfairAPI::HTTP {
    Request::Request(HttpMethod method, std::string url, 
        std::map<std::string,std::string> headers, std::string body
    ) : method_(method), url_(std::move(url)), headers_(std::move(headers)),
        body_(std::move(body)) {}

    
}