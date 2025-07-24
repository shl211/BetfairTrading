#include <iostream>
#include <thread>
#include <chrono>
#include "BetfairAPI/manager.h"
#include "BetfairAPI/stream_api.h"
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
    logger->setLevel(Logging::LogLevel::Debug);

    auto manager = BetfairAPI::BetfairManager(USERNAME,
        PASSWORD,
        APIKEYDELAY,
        BetfairAPI::Jurisdiction::UK,
        "en",
        std::unique_ptr<Logging::ILogger>(std::move(logger)));
    /*
    std::string BACK_TEAM_MATCH = "England (W)";

    BetfairAPI::BettingType::MarketFilter mf;
    mf.textQuery = BACK_TEAM_MATCH;
    
    auto r = manager.getEvents(mf);
    auto r2 = manager.getMarketCatalogues(mf,
        {BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION}
    );

    //printVector(r2);

    //grab the first market book
    auto market_id = r2[0].marketId;
    std::cout << "Querying " << market_id << "\n";

    BetfairAPI::BettingType::PriceProjection pp;
    //pp.priceData.insert(BetfairAPI::BettingEnum::PriceData::EX_TRADED);
    pp.priceData.insert(BetfairAPI::BettingEnum::PriceData::EX_ALL_OFFERS);

    auto r3 = manager.getMarketBook(
        {market_id},
        pp,
        BetfairAPI::BettingEnum::OrderProjection::EXECUTABLE,
        BetfairAPI::BettingEnum::MatchProjection::ROLLED_UP_BY_PRICE
    );

    std::cout << "Market Book \n";
    printVector(r3);

    //assuming at least one runner
    auto selection_id = r3[0].runners[0].selectionId;

    auto r4 = manager.getRunnerBook(
        market_id,
        selection_id,
        pp,
        BetfairAPI::BettingEnum::OrderProjection::EXECUTABLE,
        BetfairAPI::BettingEnum::MatchProjection::ROLLED_UP_BY_PRICE
    );

    std::cout << "Runner Book \n";
    printVector(r4);

    auto r5 = manager.getMarketProfitLoss({market_id},true,true,true);
    std::cout << "Market P&L\n";
    printVector(r5);*/

    manager.connectToStreamingService();
    std::cout << manager.readFromStreamingService() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
