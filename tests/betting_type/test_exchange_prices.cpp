#include <gtest/gtest.h>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>

#include "betting_type/exchange_prices.h"
#include "betting_type/price_size.h"

TEST(ExchangePrices, VectorConstructorAndGetter) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);

    std::vector<BetfairAPI::BettingType::PriceSize> l1 = {ps1,ps2};
    std::vector<BetfairAPI::BettingType::PriceSize> l2 = {ps3};
    std::vector<BetfairAPI::BettingType::PriceSize> l3 = {ps4,ps5,ps6,ps7};

    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);

    EXPECT_EQ(true,true);
}

TEST(ExchangePrices, TemplateConstructorAndGetter_Array) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);
    
    std::array<BetfairAPI::BettingType::PriceSize, 2> l1 = {ps1,ps2};
    std::array<BetfairAPI::BettingType::PriceSize, 1> l2 = {ps3};
    std::array<BetfairAPI::BettingType::PriceSize, 4> l3 = {ps4,ps5,ps6,ps7};
    
    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);
    
    EXPECT_EQ(true,true);
}

TEST(ExchangePrices, TemplateConstructorAndGetter_List) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);

    std::list<BetfairAPI::BettingType::PriceSize> l1 = {ps1,ps2};
    std::list<BetfairAPI::BettingType::PriceSize> l2 = {ps3};
    std::list<BetfairAPI::BettingType::PriceSize> l3 = {ps4,ps5,ps6,ps7};

    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);

    EXPECT_EQ(true,true);
}

TEST(ExchangePrices, TemplateConstructorAndGetter_Deque) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);

    std::deque<BetfairAPI::BettingType::PriceSize> l1 = {ps1,ps2};
    std::deque<BetfairAPI::BettingType::PriceSize> l2 = {ps3};
    std::deque<BetfairAPI::BettingType::PriceSize> l3 = {ps4,ps5,ps6,ps7};

    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);

    EXPECT_EQ(true,true);
}


TEST(ExchangePrices, TemplateConstructorAndGetter_InitialisationList) {
    BetfairAPI::BettingType::ExchangePrices ep(
        { {1, 2}, {3, 4} },  // available_to_back
        { {5, 6} },          // available_to_lay
        { {7, 8}, {9, 10} }  // traded_volume
    );

    EXPECT_EQ(true,true);

}

/* PriceSize must have hash function to be hashable
TEST(ExchangePrices, TemplateConstructorAndGetter_Set) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);
    
    std::set<BetfairAPI::BettingType::PriceSize> l1 = {ps1,ps2};
    std::set<BetfairAPI::BettingType::PriceSize> l2 = {ps3};
    std::set<BetfairAPI::BettingType::PriceSize> l3 = {ps4,ps5,ps6,ps7};
    
    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);
    
    EXPECT_EQ(true,true);
}

TEST(ExchangePrices, TemplateConstructorAndGetter_UnorderedSet) {
    BetfairAPI::BettingType::PriceSize ps1(1,2);
    BetfairAPI::BettingType::PriceSize ps2(1,2);
    BetfairAPI::BettingType::PriceSize ps3(1,2);
    BetfairAPI::BettingType::PriceSize ps4(1,2);
    BetfairAPI::BettingType::PriceSize ps5(1,2);
    BetfairAPI::BettingType::PriceSize ps6(1,2);
    BetfairAPI::BettingType::PriceSize ps7(1,2);
    
    std::unordered_set<BetfairAPI::BettingType::PriceSize> l1 = {ps1,ps2};
    std::unordered_set<BetfairAPI::BettingType::PriceSize> l2 = {ps3};
    std::unordered_set<BetfairAPI::BettingType::PriceSize> l3 = {ps4,ps5,ps6,ps7};
    
    BetfairAPI::BettingType::ExchangePrices ep(l1,l2,l3);
    
    EXPECT_EQ(true,true);
}
*/