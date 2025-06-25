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
    BetfairAPI::BettingType::TimeRange tr(
        BetfairAPI::Utils::Date("2026-03-13T00:00:00.000Z"),
        BetfairAPI::Utils::Date("2026-05-04T00:00:00.000Z")
    );
    mf.setMarketStartTime(tr);

    auto r = manager.listTimeRanges(mf,BetfairAPI::BettingEnum::TimeGranularity::DAYS);

    for(auto& i : r) {
        std::cout << i << "\n";
    }
    std::cout << "Total: " << r.size() << "\n";
}