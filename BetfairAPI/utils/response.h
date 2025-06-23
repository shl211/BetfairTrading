#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
namespace BetfairAPI::Utils {
    class Response {
        
    public:
        ~Response();
        Response(const cpr::Response& response);
        Response(cpr::Response&& response) noexcept;
        Response& operator=(const Response& other);
        Response& operator=(Response&& other) noexcept;
    
        const int get_status_code() const;
        const nlohmann::json& get_data() const;
    
    private:
        int status_code_;
        nlohmann::json data_;
    };
}
