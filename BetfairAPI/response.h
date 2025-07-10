#pragma once

#include "nlohmann/json.hpp"
#include <string>

namespace BetfairAPI {
    class Response {
    
        public:
            Response(int status,const std::string& raw_body);
            ~Response() = default;

            int getStatusCode() const;
            [[nodiscard]] const nlohmann::json* getBody() const;
            
        private:
            int status_code_;
            std::string body_;
            mutable nlohmann::json body_cached_;
            mutable bool already_parsed_ = false;
            mutable bool valid_json_ = false;
    };
} //namespace BetfairAPI