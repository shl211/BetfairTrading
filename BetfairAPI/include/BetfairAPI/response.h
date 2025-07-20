#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace BetfairAPI {
    class Response {
    
        public:
            Response(int status,const std::string& raw_body,const std::string& target_url);
            ~Response() = default;

            void setRequestInfo(nlohmann::json body);

            int getStatusCode() const;
            [[nodiscard]] const nlohmann::json* getBody() const;
            const std::string& getRequestTarget() const;
            [[nodiscard]] const nlohmann::json* getRequestBody() const;

            bool isReponseOk() const; 

        private:
            int status_code_;
            std::string body_;
            mutable nlohmann::json body_cached_;
            mutable bool already_parsed_ = false;
            mutable bool valid_json_ = false;
            
            //request info for logging purposes
            std::string target_url_;
            nlohmann::json request_body_;
    };
} //namespace BetfairAPI