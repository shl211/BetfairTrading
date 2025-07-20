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
    
    std::string BACK_TEAM_MATCH = "Brondby";

    BetfairAPI::BettingType::MarketFilter mf;
    mf.textQuery = BACK_TEAM_MATCH;
    
    auto r = manager.getEvents(mf);
    auto r2 = manager.getMarketCatalogues(mf,
        {BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION});

    //printVector(r);
    //printVector(r2);

    BetfairAPI::BettingType::MarketCatalogue desired_market;
    std::string targetMarketName = "Match Odds";
    auto it = std::find_if(r2.begin(), r2.end(), [&](const BetfairAPI::BettingType::MarketCatalogue& mc) {
        return mc.marketName == targetMarketName;
    });

    if (it != r2.end()) {
        desired_market = *it;
        std::cout << "Found market: " << desired_market.marketName << std::endl;
    } else {
        std::cout << "Market not found." << std::endl;
    }

    std::cout << "Selections: ";
    printVector(desired_market.runners);
    
    BetfairAPI::BettingType::RunnerCatalog runner;
    std::string targetRunner = BACK_TEAM_MATCH;
    auto it2 = std::find_if(desired_market.runners.begin(), desired_market.runners.end(), [&](const BetfairAPI::BettingType::RunnerCatalog& mc) {
        return mc.runnerName == targetRunner;
    });

    if(it2 != desired_market.runners.end()) {
        runner = *it2;
        std::cout << "Found runner: " << runner.runnerName << " (ID: " << runner.selectionId << ")" << std::endl;
    } else {
        std::cout <<"Invalid runners\n";
    }

    //place order
    BetfairAPI::BettingType::LimitOrder order;
    order.price = 1.03;
    order.size = 1;
    order.persistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    BetfairAPI::BettingType::PlaceInstruction instruction;
    instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    instruction.side = BetfairAPI::BettingEnum::Side::BACK;
    instruction.limitOrder = std::move(order);
    instruction.selectionId = runner.selectionId;

    auto order_report = manager.placeOrders(desired_market.marketId,{instruction});

    std::cout << order_report << "\n";



    std::this_thread::sleep_for(std::chrono::seconds(5));

    auto r3 = manager.getCurrentOrders();
    printVector(r3);
}