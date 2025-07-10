#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "BetfairAPI/response.h"

TEST(ResponseTest, ConstructorStoresStatus) {
    BetfairAPI::Response resp(200, R"({"key":"value"})");
    EXPECT_EQ(resp.getStatusCode(), 200);
}

TEST(ResponseTest, GetBodyParsesJsonCorrectly) {
    BetfairAPI::Response resp(200, R"({"key":"value"})");
    nlohmann::json expected = {{"key", "value"}};
    EXPECT_TRUE(resp.getBody());
    EXPECT_EQ(*resp.getBody(), expected);
}

TEST(ResponseTest, GetBodyParsesInvalidJson) {
    BetfairAPI::Response resp(200, R"(INVALID})");
    EXPECT_FALSE(resp.getBody());
}
