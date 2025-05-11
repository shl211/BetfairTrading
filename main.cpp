#include <iostream>
#include <cstdlib>

#include "BetfairAPI/BetfairManager.h"
#include "BetfairAPI/MarketFilter.h"

int main() {

    std::cout << "Testing List Market Events!" << std::endl;

    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");

    BetfairAPI::MarketFilter filter = BetfairAPI::MarketFilter();
    //filter.setInPlayOnly(true);
    filter.addEventTypeIds(BetfairAPI::EventTypeIds::RugbyUnion);
    //filter.addMarketBettingType(BetfairAPI::MarketBettingType::ASIAN_HANDICAP_SINGLE_LINE);
    BetfairAPI::BetfairManager session = BetfairAPI::BetfairManager(username,password,api_key);

    auto list = session.listCompetitions(filter);
    
    for (auto& l : list) {
        std::cout << l << "\n";
    }

}