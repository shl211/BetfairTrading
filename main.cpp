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
    mf.setQuery("Soccer");
    auto r = manager.listMarketCatalogue(mf,
        {BetfairAPI::BettingEnum::MarketProjection::COMPETITION,
        BetfairAPI::BettingEnum::MarketProjection::EVENT}//other types aren't printed in <<
    );
    std::vector<std::string> m_ids {"1.245119197","1.245101965","1.244873359"};

    auto r2 = manager.listMarketBook(m_ids);
    auto r3 = manager.listMarketProfitAndLoss(m_ids);
    auto r4 = manager.listCurrentOrders();
    printResult(r);
    printResult(r2);
    printResult(r3);
    std::cout << r4 << "\n";
}