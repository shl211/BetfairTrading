#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "http/response.h"

TEST(ResponseTest, ConstructorStoresStatus) {
    BetfairAPI::HTTP::Response resp(200, R"({"key":"value"})");
    EXPECT_EQ(resp.getStatusCode(), 200);
}

TEST(ResponseTest, GetBodyParsesJsonCorrectly) {
    BetfairAPI::HTTP::Response resp(200, R"({"key":"value"})");
    nlohmann::json expected = {{"key", "value"}};
    EXPECT_TRUE(resp.getBody());
    EXPECT_EQ(*resp.getBody(), expected);
}

TEST(ResponseTest, GetBodyParsesInvalidJson) {
    BetfairAPI::HTTP::Response resp(200, R"(INVALID})");
    EXPECT_FALSE(resp.getBody());
}
