#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace BetfairAPI::HTTP {
    class Response {
    
        public:
            Response(int status,std::string raw_body);
            ~Response() = default;

            void saveRequestInfo(nlohmann::json body);

            int getStatusCode() const;
            [[nodiscard]] const nlohmann::json* getBody() const;
            bool isResponseOk() const; 

        private:
            int status_code_;
            std::string body_;
            mutable nlohmann::json body_cached_;
            mutable bool already_parsed_ = false;
            mutable bool valid_json_ = false;
    };
} //namespace BetfairAPI