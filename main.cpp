#include <iostream>
#include <cstdlib>

#include "BetfairAPI/betfair_manager.h"

int main() {

    std::cout << "Testing Login!" << std::endl;
    
    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");
    
    BetfairAPI::BetfairManager manager(username,password,api_key);
    std::cout << manager.getAccountBalance() << "\n";
    
    BetfairAPI::BettingType::MarketFilter mf;
    mf.addVenue("Harlow");
    auto r = manager.listEvents(mf);

    for(auto& i : r) {
        std::cout << i << "\n";
    }
    std::cout << "Total: " << r.size() << "\n";
}