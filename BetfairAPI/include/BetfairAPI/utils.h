#pragma once

#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <stdexcept>
#include <type_traits>
#include <magic_enum.hpp>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

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


    inline std::string unixToISO8601(std::time_t timestamp) {
        std::tm tm{};
        
    #ifdef _WIN32
        if (gmtime_s(&tm, &timestamp) != 0) {
            throw std::runtime_error("Failed to convert time to UTC");
        }
    #else
        if (gmtime_r(&timestamp, &tm) == nullptr) {
            throw std::runtime_error("Failed to convert time to UTC");
        }
    #endif

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        if (oss.fail()) {
            throw std::runtime_error("Failed to format time as ISO8601");
        }
        return oss.str();
    }

    inline std::time_t iso8601ToUnix(const std::string& iso_time) {
        std::tm tm = {};
        std::istringstream ss(iso_time);

        // Try to parse the ISO format (e.g., "2025-08-05T20:00:00Z")
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse ISO8601 time: " + iso_time);
        }

        // Convert to time_t (UTC)
    #ifdef _WIN32
        std::time_t result = _mkgmtime(&tm);
    #else
        std::time_t result = timegm(&tm);
    #endif

        if (result == -1) {
            throw std::runtime_error("Failed to convert tm to time_t");
        }
        return result;
    }
}