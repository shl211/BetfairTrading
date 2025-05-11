#include "Response.h"

namespace BetfairAPI {
    Response::~Response() {
        //do nothing
    }
    
    Response::Response(const cpr::Response& response) : 
        status_code_(response.status_code),
        data_(nlohmann::json::parse(response.text)) {}
    
    Response::Response(cpr::Response&& response) noexcept : 
        status_code_(std::move(response.status_code)),
        data_(std::move(nlohmann::json::parse(response.text))) {}
    
    Response& Response::operator=(const Response& other) {
        if (this != &other) {
            status_code_ = other.status_code_;
            data_ = other.data_;
        }
    
        return *this;
    }
    
    Response& Response::operator=(Response&& other) noexcept {
        if (this != &other) {
            status_code_ = other.status_code_;
            data_ = std::move(other.data_);
        }
        return *this;
    }
    
    const int Response::get_status_code() const {
        return status_code_;
    }
    
    const nlohmann::json& Response::get_data() const {
        return data_;
    }
}

