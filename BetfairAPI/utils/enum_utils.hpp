#pragma once

#include <string>
#include <magic_enum.hpp>
#include <stdexcept>

namespace BetfairAPI::Utils {
    template<typename Enum>
    std::string to_string(Enum value) {
        return std::string(magic_enum::enum_name(value));
    };

    template<typename Enum>
    Enum from_string(std::string_view name) {
        auto result = magic_enum::enum_cast<Enum>(name);
        if (!result) {
            throw std::invalid_argument("Invalid enum string: " + std::string(name));
        }
        return result.value();
    };
}