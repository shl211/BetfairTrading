#include "Response.h"

Response::~Response() {
    //do nothing
}

Response::Response(cpr::Response response) : 
    status_code(response.status_code),
    data(nlohmann::json::parse(response.text)) {}

Response::Response(const cpr::Response& response) : 
    status_code(response.status_code),
    data(nlohmann::json::parse(response.text)) {}

Response::Response(cpr::Response&& response) noexcept : 
    status_code(response.status_code),
    data(nlohmann::json::parse(response.text)) {}

Response& Response::operator=(const Response& other) {
    if (this != &other) {
        status_code = other.status_code;
        data = other.data;
    }

    return *this;
}

Response& Response::operator=(Response&& other) noexcept {
    if (this != &other) {
        status_code = other.status_code;
        data = std::move(other.data);
    }
    return *this;
}

const int Response::get_status_code() const {
    return status_code;
}

const nlohmann::json& Response::get_data() const {
    return data;
}

