#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cxxopts.hpp>

#include "BetfairAPI/manager.h"
#include "Logging/console_logger.h"
#include "Logging/coloured_console_logger.h"

template <typename T>
void printVector(const std::vector<T>& v) {
    for (const auto& i : v) {
        std::cout << i << "\n";
    }
    std::cout << "Total: " << v.size() << "\n";
}

int main(int argc, char** argv) {
    cxxopts::Options options("BetfairExample", "CLI interface to place Betfair orders");

    options.add_options()
        ("USERNAME", "Betfair username", cxxopts::value<std::string>())
        ("PASSWORD", "Betfair password", cxxopts::value<std::string>())
        ("TOKEN", "Betfair API token", cxxopts::value<std::string>())
        ("EVENT", "Selected event", cxxopts::value<std::string>())
        ("RUNNER", "Selected runner", cxxopts::value<std::string>())
        ("MARKET", "Selected market", cxxopts::value<std::string>())
        ("ORDER_PRICE", "Order price", cxxopts::value<double>())
        ("ORDER_SIZE", "Order size", cxxopts::value<double>())
        ("SIDE", "Betting side (BACK or LAY)", cxxopts::value<std::string>()->default_value("BACK"))
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") ||
        !result.count("USERNAME") || 
        !result.count("PASSWORD") || 
        !result.count("TOKEN") || 
        !result.count("EVENT") || 
        !result.count("MARKET") || 
        !result.count("ORDER_PRICE") || 
        !result.count("ORDER_SIZE") || 
        !result.count("RUNNER")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    std::string username = result["USERNAME"].as<std::string>();
    std::string password = result["PASSWORD"].as<std::string>();
    std::string token = result["TOKEN"].as<std::string>();
    std::string desired_event = result["EVENT"].as<std::string>();
    std::string desired_runner = result["RUNNER"].as<std::string>();
    std::string desired_market = result["MARKET"].as<std::string>();
    double desired_price = result["ORDER_PRICE"].as<double>();
    double desired_size = result["ORDER_SIZE"].as<double>();
    std::string sideStr = result["SIDE"].as<std::string>();

    auto logger = std::make_unique<Logging::ColouredConsoleLogger>();
    logger->setLevel(Logging::LogLevel::Info);

    BetfairAPI::BetfairManager manager(
        username,
        password,
        token,
        BetfairAPI::Jurisdiction::UK,
        "en",
        std::move(logger)
    );

    //get desired events
    BetfairAPI::BettingType::MarketFilter mf;
    mf.textQuery = desired_event;

    auto events = manager.getEvents(mf);
    auto markets = manager.getMarketCatalogues(mf, {
        BetfairAPI::BettingEnum::MarketProjection::RUNNER_DESCRIPTION
    });

    BetfairAPI::BettingType::MarketCatalogue selected_market;

    //match correct market
    auto market_it = std::find_if(markets.begin(), markets.end(), [&](const auto& m) {
        return m.marketName == desired_market;
    });

    if (market_it == markets.end()) {
        std::cerr << "Market not found.\n";
        return 1;
    }

    selected_market = *market_it;
    std::cout << "Found market: " << selected_market.marketName << "\n";
    printVector(selected_market.runners);

    auto runner_it = std::find_if(selected_market.runners.begin(), selected_market.runners.end(),
        [&](const auto& r) { return r.runnerName == desired_runner; });

    if (runner_it == selected_market.runners.end()) {
        std::cerr << "Runner not found.\n";
        return 1;
    }

    auto runner = *runner_it;
    std::cout << "Found runner: " << runner.runnerName << " (ID: " << runner.selectionId << ")\n";

    BetfairAPI::BettingType::LimitOrder order;
    order.price = desired_price;
    order.size = desired_size;
    order.persistenceType = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    BetfairAPI::BettingType::PlaceInstruction instruction;
    instruction.orderType = BetfairAPI::BettingEnum::OrderType::LIMIT;
    instruction.side = (sideStr == "LAY" ? BetfairAPI::BettingEnum::Side::LAY : BetfairAPI::BettingEnum::Side::BACK);
    instruction.limitOrder = std::move(order);
    instruction.selectionId = runner.selectionId;

    auto order_report = manager.placeOrders(selected_market.marketId, {instruction});
    std::cout << order_report << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));

    auto open_orders = manager.getCurrentOrders();
    printVector(open_orders);

    return 0;
}
