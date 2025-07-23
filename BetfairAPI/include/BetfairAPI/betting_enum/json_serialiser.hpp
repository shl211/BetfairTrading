#pragma once

#include <type_traits>
#include <nlohmann/json.hpp>
#include "BetfairAPI/utils.h"

namespace BetfairAPI::BettingEnum {
    template <typename Enum>
    inline auto to_json(nlohmann::json& j, Enum e) -> std::enable_if_t<std::is_enum_v<Enum>,void>
    {
        j = to_string<Enum>(e);
    };

    template <typename Enum>
    inline auto from_json(const nlohmann::json& j, Enum& e) -> std::enable_if_t<std::is_enum_v<Enum>,void>
    {
        e = from_string<Enum>(j.get<std::string>());
    };
}