#pragma once

#include <nlohmann/json.hpp>
#include "BetfairAPI/account_type/account_funds_response.h"

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
}