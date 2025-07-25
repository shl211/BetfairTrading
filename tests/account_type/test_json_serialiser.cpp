#include <gtest/gtest.h>

#include "BetfairAPI/account_type/json_serialiser.hpp"

TEST(AccountFundsResponseJson,Basic)  {
    BetfairAPI::AccountType::AccountFundsResponse funds;
    funds.availableToBetBalance = 10.2;
    funds.exposure = 0.2;
    funds.retainedCommission = 0.0;
    funds.discountRate = 100.0;
    funds.pointsBalance = 1;

    nlohmann::json j = funds;
    auto obj = j.get<BetfairAPI::AccountType::AccountFundsResponse>();

    EXPECT_EQ(funds,obj);
}

TEST(AccountDetailsResponseJson,Basic)  {
    BetfairAPI::AccountType::AccountDetailsResponse details;
    details.currencyCode = "GBP";
    details.firstName = "John";
    details.lastName = "Doe";
    details.localeCode = "en";
    details.timezone = "Europe/London";
    details.discountRate = 5.0;
    details.pointsBalance = 100;

    nlohmann::json j = details;
    auto obj = j.get<BetfairAPI::AccountType::AccountDetailsResponse>();

    EXPECT_EQ(details, obj);
}

TEST(TimeRangeJson,Basic)  {
    BetfairAPI::AccountType::TimeRange range;
    range.from = BetfairAPI::Date("2024-06-01T12:00:00Z");
    range.to = BetfairAPI::Date("2024-06-02T12:00:00Z");

    nlohmann::json j = range;
    auto obj = j.get<BetfairAPI::AccountType::TimeRange>();

    EXPECT_EQ(range, obj);
}

TEST(StatementItemJson,Basic)  {
    BetfairAPI::AccountType::StatementItem item;
    item.refId = "REF123";
    item.itemDate = BetfairAPI::Date("2024-06-01T15:30:00Z");
    item.amount = 50.0;
    item.balance = 150.0;
    item.itemClassData = {{"key1", "value1"}, {"key2", "value2"}};

    nlohmann::json j = item;
    auto obj = j.get<BetfairAPI::AccountType::StatementItem>();

    EXPECT_EQ(item, obj);
}

TEST(AccountStatementReportJson,Basic)  {
    BetfairAPI::AccountType::AccountStatementReport report;
    BetfairAPI::AccountType::StatementItem item;
    item.refId = "REF123";
    item.itemDate = BetfairAPI::Date("2024-06-01T15:30:00Z");
    item.amount = 50.0;
    item.balance = 150.0;
    item.itemClassData = {{"key1", "value1"}, {"key2", "value2"}};
    report.accountStatement.push_back(item);
    report.moreAvailable = true;

    nlohmann::json j = report;
    auto obj = j.get<BetfairAPI::AccountType::AccountStatementReport>();

    EXPECT_EQ(report, obj);
}