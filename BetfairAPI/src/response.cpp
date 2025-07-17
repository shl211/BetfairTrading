#include "BetfairAPI/response.h"

namespace BetfairAPI {

    namespace {
        constexpr std::nullptr_t disable_error_callback = nullptr;
        constexpr bool allow_exceptions = false;
    }

    Response::Response(int status,const std::string& raw_body)
        : status_code_(status), body_(raw_body) {}

    int Response::getStatusCode() const {
        return status_code_;
    }

    const nlohmann::json* Response::getBody() const {
        if(!already_parsed_) {

            body_cached_ = nlohmann::json::parse(body_,disable_error_callback,allow_exceptions);
            already_parsed_ = true;
            valid_json_ = !body_cached_.is_discarded();
        }
        
        return valid_json_ ? &body_cached_ : nullptr;
    }

    void Response::setRequestInfo(std::string target,nlohmann::json body) {
        target_url_ = std::move(target);
        request_body_ = std::move(body);
    }

    const std::string& Response::getRequestTarget() const {
        return target_url_;
    }
    
    const nlohmann::json* Response::getRequestBody() const {
        return request_body_.is_null() ? nullptr : &request_body_;
    }
} //namespace BetfairAPI