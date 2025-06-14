#include "gtest/gtest.h"
#include "betting_type/market_license.h"

TEST(MarketLicense, ConstructorAndGetter) {
    std::string rules = "RULES";
    std::string wallet = "Exchange";
    std::string clarifications = "Clarify";
    bool rules_has_date = false;

    BetfairAPI::BettingType::MarketLicense license(wallet,rules,rules_has_date,clarifications);

    EXPECT_EQ(license.getWallet(),wallet);
    EXPECT_EQ(license.getRules(),rules);
    EXPECT_EQ(license.getClarifications(),clarifications);
    EXPECT_EQ(license.isRulesHasDate(),rules_has_date);
}