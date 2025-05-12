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
    filter.addEventTypeIds(BetfairAPI::EventTypeIds::Soccer);
    BetfairAPI::BetfairManager session = BetfairAPI::BetfairManager(username,password,api_key);

    auto list = session.listEvents(filter);
    std::cout << list << "\n";
    //for (auto& l : list) {
    //    std::cout << l << "\n";
    //}

}