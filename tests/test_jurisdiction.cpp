#include <gtest/gtest.h>
#include "BetfairAPI/jurisdiction.hpp"


TEST(Jurisdiction,GetURL) {    
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::GLOBAL), BetfairAPI::detail::global_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::ITALY), BetfairAPI::detail::italy_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::SPAIN), BetfairAPI::detail::spain_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::ROMANIA), BetfairAPI::detail::romania_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::SWEDEN), BetfairAPI::detail::sweden_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::NEWZEALAND), BetfairAPI::detail::new_zealand_australia_url);
    EXPECT_EQ(BetfairAPI::getBetfairUrl(BetfairAPI::Jurisdiction::AUSTRALIA), BetfairAPI::detail::new_zealand_australia_url);

    //default to global 
    EXPECT_EQ(BetfairAPI::getBetfairUrl(static_cast<BetfairAPI::Jurisdiction>(-1)), BetfairAPI::detail::global_url);
}