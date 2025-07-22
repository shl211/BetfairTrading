#pragma once

#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <magic_enum.hpp>
#include <stdexcept>
#include <type_traits>

namespace BetfairAPI {

    /**************************************************************************
     * Convert Enum to string
     *************************************************************************/

    // Base case: Only works for real enums (not containers)
    template<typename Enum>
    inline auto to_string(Enum value) 
        -> std::enable_if_t<std::is_enum_v<Enum>, std::string>
    {
        return std::string(magic_enum::enum_name(value));
    }

    // Specialization for std::vector
    template<typename Enum>
    inline std::vector<std::string> to_string(const std::vector<Enum>& values) {
        std::vector<std::string> result;
        result.reserve(values.size());
        for (const auto& value : values) {
            result.push_back(to_string(value));
        }
        return result;
    }

    // Specialization for std::set
    template<typename Enum>
    inline std::set<std::string> to_string(const std::set<Enum>& values) {
        std::set<std::string> result;
        for (const auto& value : values) {
            result.insert(to_string(value));
        }
        return result;
    }

    /**************************************************************************
     * Convert string to Enum
     *************************************************************************/

    // Base case: Only works for real enums (not containers)
    template<typename Enum>
    inline auto from_string(const std::string& name) 
        -> std::enable_if_t<std::is_enum_v<Enum>, Enum> 
    {
        auto opt = magic_enum::enum_cast<Enum>(name);

        if (!opt.has_value()) {
            throw std::invalid_argument("Invalid enum name: " + name);
        }
        return opt.value();
    }

    // Specialization for std::vector
    template<typename Enum>
    inline std::vector<Enum> from_string(const std::vector<std::string>& name) {
        std::vector<Enum> result;
        result.reserve(std::size(name));
        for (const auto& v : name) {
            result.push_back(from_string<Enum>(v));
        }
        return result;
    };
    
    // Specialization for std::set
    template<typename Enum>
    inline std::set<Enum> from_string(const std::set<std::string>& name) {
        std::set<Enum> result;
        for (const auto& v : name) {
            result.insert(from_string<Enum>(v));
        }
        return result;
    };
}