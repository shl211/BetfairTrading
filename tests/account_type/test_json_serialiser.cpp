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