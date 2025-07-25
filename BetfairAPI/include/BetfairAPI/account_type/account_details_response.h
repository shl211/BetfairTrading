#pragma once

#include <string>
#include <optional>
#include <ostream>


namespace BetfairAPI::AccountType {
    struct AccountDetailsResponse {
        std::optional<std::string> currencyCode;
        std::optional<std::string> firstName;
        std::optional<std::string> lastName;
        std::optional<std::string> localeCode;
        std::optional<std::string> timezone;
        std::optional<double> discountRate;
        std::optional<int> pointsBalance;
        std::optional<std::string> countryCode;
    };

    inline bool operator==(const AccountDetailsResponse& lhs, const AccountDetailsResponse& rhs) {
        return lhs.currencyCode == rhs.currencyCode &&
               lhs.firstName == rhs.firstName &&
               lhs.lastName == rhs.lastName &&
               lhs.localeCode == rhs.localeCode &&
               lhs.timezone == rhs.timezone &&
               lhs.discountRate == rhs.discountRate &&
               lhs.pointsBalance == rhs.pointsBalance &&
               lhs.countryCode == rhs.countryCode;
    }

    inline bool operator!=(const AccountDetailsResponse& lhs, const AccountDetailsResponse& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const AccountDetailsResponse& resp) {
        os << "AccountDetailsResponse{";
        os << "currencyCode=" << (resp.currencyCode ? *resp.currencyCode : "null") << ", ";
        os << "firstName=" << (resp.firstName ? *resp.firstName : "null") << ", ";
        os << "lastName=" << (resp.lastName ? *resp.lastName : "null") << ", ";
        os << "localeCode=" << (resp.localeCode ? *resp.localeCode : "null") << ", ";
        os << "timezone=" << (resp.timezone ? *resp.timezone : "null") << ", ";
        os << "discountRate=" << (resp.discountRate ? std::to_string(*resp.discountRate) : "null") << ", ";
        os << "pointsBalance=" << (resp.pointsBalance ? std::to_string(*resp.pointsBalance) : "null") << ", ";
        os << "countryCode=" << (resp.countryCode ? *resp.countryCode : "null");
        os << "}";
        return os;
    }
}