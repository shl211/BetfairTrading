#pragma once

#include <nlohmann/json.hpp>
#include "BetfairAPI/account_type/account_funds_response.h"
#include "BetfairAPI/account_type/account_details_response.h"

namespace BetfairAPI::AccountType {
    /**************************************************************************
    * AccountFundsResponse
    **************************************************************************/
    void to_json(nlohmann::json& j, const AccountFundsResponse& obj) {
        if (obj.availableToBetBalance) j["availableToBetBalance"] = obj.availableToBetBalance.value();
        if (obj.exposure) j["exposure"] = obj.exposure.value();
        if (obj.retainedCommission) j["retainedCommission"] = obj.retainedCommission.value();
        if (obj.exposureLimit) j["exposureLimit"] = obj.exposureLimit.value();
        if (obj.discountRate) j["discountRate"] = obj.discountRate.value();
        if (obj.pointsBalance) j["pointsBalance"] = obj.pointsBalance.value();
    }

    void from_json(const nlohmann::json& j, AccountFundsResponse& obj) {
        if (j.contains("availableToBetBalance")) obj.availableToBetBalance = j.at("availableToBetBalance").get<double>();
        if (j.contains("exposure")) obj.exposure = j.at("exposure").get<double>();
        if (j.contains("retainedCommission")) obj.retainedCommission = j.at("retainedCommission").get<double>();
        if (j.contains("exposureLimit")) obj.exposureLimit = j.at("exposureLimit").get<double>();
        if (j.contains("discountRate")) obj.discountRate = j.at("discountRate").get<double>();
        if (j.contains("pointsBalance")) obj.pointsBalance = j.at("pointsBalance").get<int>();
    }

    /**************************************************************************
    * AccountDetailsResponse
    **************************************************************************/
    void to_json(nlohmann::json& j, const AccountDetailsResponse& obj) {
        if (obj.currencyCode) j["currencyCode"] = obj.currencyCode.value();
        if (obj.firstName) j["firstName"] = obj.firstName.value();
        if (obj.lastName) j["lastName"] = obj.lastName.value();
        if (obj.localeCode) j["localeCode"] = obj.localeCode.value();
        if (obj.timezone) j["timezone"] = obj.timezone.value();
        if (obj.discountRate) j["discountRate"] = obj.discountRate.value();
        if (obj.pointsBalance) j["pointsBalance"] = obj.pointsBalance.value();
        if (obj.countryCode) j["countryCode"] = obj.countryCode.value();
    }

    void from_json(const nlohmann::json& j, AccountDetailsResponse& obj) {
        if (j.contains("currencyCode")) obj.currencyCode = j.at("currencyCode").get<std::string>();
        if (j.contains("firstName")) obj.firstName = j.at("firstName").get<std::string>();
        if (j.contains("lastName")) obj.lastName = j.at("lastName").get<std::string>();
        if (j.contains("localeCode")) obj.localeCode = j.at("localeCode").get<std::string>();
        if (j.contains("timezone")) obj.timezone = j.at("timezone").get<std::string>();
        if (j.contains("discountRate")) obj.discountRate = j.at("discountRate").get<double>();
        if (j.contains("pointsBalance")) obj.pointsBalance = j.at("pointsBalance").get<int>();
        if (j.contains("countryCode")) obj.countryCode = j.at("countryCode").get<std::string>();
    }
}