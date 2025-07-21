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
        ("BET_ID", "Selected bet to cancel, if neither BET_ID nor MARKET_ID specified, will cancel all unmatched orders", cxxopts::value<std::string>()->default_value(""))
        ("MARKET_ID", "Selected market to cancel bets, if neither BET_ID nor MARKET_ID  specified, will cancel all unmatched orders", cxxopts::value<std::string>()->default_value(""))
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") ||
        !result.count("USERNAME") || 
        !result.count("PASSWORD") || 
        !result.count("TOKEN")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    std::string username = result["USERNAME"].as<std::string>();
    std::string password = result["PASSWORD"].as<std::string>();
    std::string token = result["TOKEN"].as<std::string>();
    std::string bet_id = result["BET_ID"].as<std::string>();
    std::string market_id = result["MARKET_ID"].as<std::string>();

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

    manager.getCurrentOrders();

    BetfairAPI::BettingType::CancelInstruction instruction;
    if(!bet_id.empty()) instruction.betId = bet_id;

    std::vector<BetfairAPI::BettingType::CancelInstruction> orders;
    if(!instruction.betId.empty()) orders.push_back(std::move(instruction));

    auto cancelReport = manager.cancelOrders(market_id,orders);

    std::cout << cancelReport << "\n";
}