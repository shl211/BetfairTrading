#include <iostream>
#include <thread>
#include <chrono>
#include "BetfairAPI/manager.h"
#include "Logging/console_logger.h"
#include "Logging/coloured_console_logger.h"
#include "Logging/file_logger.h"

template <typename T>
void printVector(std::vector<T> v) {
    for(auto& i : v) {
        std::cout << i << "\n";
    }
    std::cout << "Total: " << v.size() << "\n";
};

int main() {
    const char* USERNAME = std::getenv("USERNAME");
    const char* PASSWORD = std::getenv("PASSWORD");
    const char* APIKEYDELAY = std::getenv("APIKEYDELAY");
    if (!USERNAME || !PASSWORD || !APIKEYDELAY) {
        std::cerr << "Environment variables BETFAIR_USERNAME, BETFAIR_PASSWORD, or BETFAIR_APIKEYDELAY not set." << std::endl;
        return 1;
    }

    auto logger = std::make_unique<Logging::ColouredConsoleLogger>();
    logger->setLevel(Logging::LogLevel::Info);

    auto manager = BetfairAPI::BetfairManager(USERNAME,
        PASSWORD,
        APIKEYDELAY,
        BetfairAPI::Jurisdiction::UK,
        "en",
        std::unique_ptr<Logging::ILogger>(std::move(logger)));
    
    BetfairAPI::BettingType::MarketFilter mf;
    //mf.inPlayOnly = true;
    auto r = manager.getMarketCatalogues(mf,
        {BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION,
        BetfairAPI::BettingEnum::MarketProjection::RUNNER_METADATA,
        BetfairAPI::BettingEnum::MarketProjection::EVENT_TYPE,
        },
        {},
        10);
    printVector(r);

    std::set<std::string> bet_ids;
    for (int i = 0; i < 251; ++i) {
        bet_ids.insert("bet_id_" + std::to_string(i));
    }

    auto r2 = manager.getCurrentOrders(bet_ids);

    printVector(r2);

    //std::this_thread::sleep_for(std::chrono::minutes(5));
}