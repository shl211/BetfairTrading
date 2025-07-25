#pragma once

#include <nlohmann/json.hpp>
#include "BetfairAPI/utils.h"
#include "BetfairAPI/account_type/account_funds_response.h"
#include "BetfairAPI/account_type/account_details_response.h"
#include "BetfairAPI/account_type/time_range.h"
#include "BetfairAPI/account_type/statement_item.h"
#include "BetfairAPI/account_type/account_statement_report.h"

namespace BetfairAPI::AccountType {
    /**************************************************************************
    * AccountFundsResponse
    **************************************************************************/
    inline void to_json(nlohmann::json& j, const AccountFundsResponse& obj) {
        if (obj.availableToBetBalance) j["availableToBetBalance"] = obj.availableToBetBalance.value();
        if (obj.exposure) j["exposure"] = obj.exposure.value();
        if (obj.retainedCommission) j["retainedCommission"] = obj.retainedCommission.value();
        if (obj.exposureLimit) j["exposureLimit"] = obj.exposureLimit.value();
        if (obj.discountRate) j["discountRate"] = obj.discountRate.value();
        if (obj.pointsBalance) j["pointsBalance"] = obj.pointsBalance.value();
    }

    inline void from_json(const nlohmann::json& j, AccountFundsResponse& obj) {
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
    inline void to_json(nlohmann::json& j, const AccountDetailsResponse& obj) {
        if (obj.currencyCode) j["currencyCode"] = obj.currencyCode.value();
        if (obj.firstName) j["firstName"] = obj.firstName.value();
        if (obj.lastName) j["lastName"] = obj.lastName.value();
        if (obj.localeCode) j["localeCode"] = obj.localeCode.value();
        if (obj.timezone) j["timezone"] = obj.timezone.value();
        if (obj.discountRate) j["discountRate"] = obj.discountRate.value();
        if (obj.pointsBalance) j["pointsBalance"] = obj.pointsBalance.value();
        if (obj.countryCode) j["countryCode"] = obj.countryCode.value();
    }

    inline void from_json(const nlohmann::json& j, AccountDetailsResponse& obj) {
        if (j.contains("currencyCode")) obj.currencyCode = j.at("currencyCode").get<std::string>();
        if (j.contains("firstName")) obj.firstName = j.at("firstName").get<std::string>();
        if (j.contains("lastName")) obj.lastName = j.at("lastName").get<std::string>();
        if (j.contains("localeCode")) obj.localeCode = j.at("localeCode").get<std::string>();
        if (j.contains("timezone")) obj.timezone = j.at("timezone").get<std::string>();
        if (j.contains("discountRate")) obj.discountRate = j.at("discountRate").get<double>();
        if (j.contains("pointsBalance")) obj.pointsBalance = j.at("pointsBalance").get<int>();
        if (j.contains("countryCode")) obj.countryCode = j.at("countryCode").get<std::string>();
    }

    /**************************************************************************
    * TimeRange  
    **************************************************************************/
    inline void to_json(nlohmann::json& j,const TimeRange& tr) {
        if(tr.from) j["from"] = tr.from->getIsoString();
        if(tr.to) j["to"] = tr.to->getIsoString();
    }

    inline void from_json(const nlohmann::json& j, TimeRange& tr) {
        if(j.contains("from")) tr.from = BetfairAPI::Date(j.at("from").get<std::string>());
        if(j.contains("to")) tr.to = BetfairAPI::Date(j.at("to").get<std::string>());
    }

    /**************************************************************************
    * StatementItem  
    **************************************************************************/
    inline void to_json(nlohmann::json& j,const StatementItem& tr) {
        j["refId"] = tr.refId;
        if (tr.itemDate) j["itemDate"] = tr.itemDate->getIsoString();
        if (tr.amount) j["amount"] = tr.amount.value();
        if (tr.balance) j["balance"] = tr.balance.value();
        if (tr.itemClass) j["itemClass"] = to_string(tr.itemClass.value());
        if (!tr.itemClassData.empty()) j["itemClassData"] = tr.itemClassData;
    }

    inline void from_json(const nlohmann::json& j, StatementItem& tr) {
        if (j.contains("refId")) tr.refId = j.at("refId").get<std::string>();
        if (j.contains("itemDate")) tr.itemDate = BetfairAPI::Date(j.at("itemDate").get<std::string>());
        if (j.contains("amount")) tr.amount = j.at("amount").get<double>();
        if (j.contains("balance")) tr.balance = j.at("balance").get<double>();
        if (j.contains("itemClass")) tr.itemClass = from_string<AccountEnum::ItemClass>(j.at("itemClass").get<std::string>());
        if (j.contains("itemClassData")) tr.itemClassData = j.at("itemClassData").get<std::map<std::string,std::string>>();
    }

    /**************************************************************************
    * AccountStatementReport  
    **************************************************************************/
    inline void to_json(nlohmann::json& j,const AccountStatementReport& tr) {
        j["accountStatement"] = tr.accountStatement;
        j["moreAvailable"] = tr.moreAvailable;
    }

    inline void from_json(const nlohmann::json& j, AccountStatementReport& tr) {
        if (j.contains("accountStatement")) tr.accountStatement = j.at("accountStatement").get<std::vector<StatementItem>>();
        if (j.contains("moreAvailable")) tr.moreAvailable = j.at("moreAvailable").get<bool>();
    }
}