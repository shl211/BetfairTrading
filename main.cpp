#include <iostream>
#include <cstdlib>

#include "BetfairAPI/BetfairManager.h"
#include "BetfairAPI/MarketFilter.h"

int main() {

    std::cout << "Testing Login API!" << std::endl;

    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");

    BetfairAPI::MarketFilter filter = BetfairAPI::MarketFilter();
    filter.setInPlay(true);
    BetfairAPI::BetfairManager session = BetfairAPI::BetfairManager(username,password,api_key);

    std::cout << session.listEventTypes(filter) << "\n";

}