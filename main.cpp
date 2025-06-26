#include <iostream>
#include <cstdlib>

#include "BetfairAPI/betfair_manager.h"

template<typename T>
void printResult(std::vector<T> vec) {
    for(auto& v : vec) {
        std::cout << v << "\n";
    }
    std::cout << "Total: " << vec.size() << "\n";
}

int main() {

    std::cout << "Testing Login!" << std::endl;
    
    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");
    
    BetfairAPI::BetfairManager manager(username,password,api_key);
    std::cout << manager.getAccountBalance() << "\n";
    
    BetfairAPI::BettingType::MarketFilter mf;
    auto r = manager.listMarketCatalogue(mf,
        {BetfairAPI::BettingEnum::MarketProjection::COMPETITION,
        BetfairAPI::BettingEnum::MarketProjection::EVENT}//other types aren't printed in <<
    );

    auto r2 = manager.listMarketBook(
        {"1.245119197"}
    );
    printResult(r2);
}