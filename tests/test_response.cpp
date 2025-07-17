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

TEST(ResponseTest, GetRequestInfo) {
    nlohmann::json j {"Some","Request"};
    std::string url {"https://something.somewhere"};

    BetfairAPI::Response resp{200,R"({"key":"value"})"};

    //test to make sure no request info before input
    EXPECT_FALSE(resp.getRequestBody());
    EXPECT_TRUE(resp.getRequestTarget().empty());

    //now insert
    resp.setRequestInfo(url,j);
    EXPECT_TRUE(!resp.getRequestTarget().empty());
    EXPECT_TRUE(resp.getRequestBody());

    EXPECT_EQ(url,resp.getRequestTarget());
    EXPECT_EQ(j,*resp.getRequestBody());

}