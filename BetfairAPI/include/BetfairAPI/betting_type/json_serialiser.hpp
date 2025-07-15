#pragma once

#include <nlohmann/json.hpp>

namespace BetfairAPI::BettingType {
    template<typename T>
    struct JsonSer {
        // These should be specialised per type
        static nlohmann::json toJson(const T& obj);
        static T fromJson(const nlohmann::json& j);
    };
    
    //Cleaner syntax for users
    template<typename T>
    nlohmann::json toJson(const T& obj) {
        return JsonSer<T>::toJson(obj);
    }
    
    template<typename T>
    T fromJson(const nlohmann::json& j) {
        return JsonSer<T>::fromJson(j);
    }
}
