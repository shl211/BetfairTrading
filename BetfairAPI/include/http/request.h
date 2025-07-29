#pragma once

#include <string>
#include <map>

namespace BetfairAPI::HTTP {
    class Request {
        public:
            enum HttpMethod { GET, POST, PUT, DELETE };
            
            Request(HttpMethod method, std::string url, 
                std::map<std::string,std::string> headers = {}, std::string body = ""
            );

            const std::map<std::string, std::string>& header() const {return headers_;};
            const std::string& url() const {return url_;};
            const std::string& body() const {return body_;};
            HttpMethod method() const {return method_;};

        private:
            std::string url_;
            std::map<std::string, std::string> headers_;
            std::string body_;
            HttpMethod method_;
    };
}