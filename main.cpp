#include <iostream>
#include <thread>
#include <chrono>
#include "BetfairAPI/manager.h"
#include "Logging/console_logger.h"
#include "Logging/file_logger.h"

int main() {
    const char* USERNAME = std::getenv("USERNAME");
    const char* PASSWORD = std::getenv("PASSWORD");
    const char* APIKEYDELAY = std::getenv("APIKEYDELAY");
    if (!USERNAME || !PASSWORD || !APIKEYDELAY) {
        std::cerr << "Environment variables BETFAIR_USERNAME, BETFAIR_PASSWORD, or BETFAIR_APIKEYDELAY not set." << std::endl;
        return 1;
    }

    auto manager = BetfairAPI::BetfairManager(USERNAME,
        PASSWORD,
        APIKEYDELAY,
        BetfairAPI::Jurisdiction::UK,
        "en",
        std::make_unique<Logging::ConsoleLogger>());
    
    BetfairAPI::BettingType::MarketFilter mf;
    //mf.inPlayOnly = true;
    auto r = manager.getMarketCatalogues(mf,
        {BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION,
        BetfairAPI::BettingEnum::MarketProjection::RUNNER_METADATA,
        BetfairAPI::BettingEnum::MarketProjection::EVENT_TYPE,
        },
        {},
        10);

    for(auto& v : r) {
        std::cout << v << "\n";
    }
    std::cout << "Total: " << r.size() << "\n";

    //std::this_thread::sleep_for(std::chrono::minutes(5));
}