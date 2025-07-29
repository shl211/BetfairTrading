#include "http/response.h"

namespace BetfairAPI::HTTP {

    namespace {
        constexpr std::nullptr_t disable_error_callback = nullptr;
        constexpr bool allow_exceptions = false;
    }

    Response::Response(int status,std::string raw_body)
        : status_code_(status), body_(std::move(raw_body)) {}

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

    bool Response::isResponseOk() const {
        return status_code_ < 300 && status_code_ >= 200;
    } 

} //namespace BetfairAPI