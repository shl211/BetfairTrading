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
    cxxopts::Options options("BetfairExample", "CLI interface to replace Betfair orders.");

    options.add_options()
        ("USERNAME", "Betfair username", cxxopts::value<std::string>())
        ("PASSWORD", "Betfair password", cxxopts::value<std::string>())
        ("TOKEN", "Betfair API token", cxxopts::value<std::string>())
        ("BETID", "Selected market", cxxopts::value<std::string>())
        ("MARKETID", "Selected market", cxxopts::value<std::string>())
        ("NEW_BET_PRICE", "New bet price", cxxopts::value<double>())
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") ||
        !result.count("USERNAME") || 
        !result.count("PASSWORD") || 
        !result.count("TOKEN") || 
        !result.count("BETID") || 
        !result.count("MARKETID") || 
        !result.count("NEW_BET_PRICE")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    std::string username = result["USERNAME"].as<std::string>();
    std::string password = result["PASSWORD"].as<std::string>();
    std::string token = result["TOKEN"].as<std::string>();
    std::string market_id = result["MARKETID"].as<std::string>();
    std::string bet_id = result["BETID"].as<std::string>();
    double new_bet_price = result["NEW_BET_PRICE"].as<double>();

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

    // Replace order
    BetfairAPI::BettingType::ReplaceInstruction replace_instr;
    replace_instr.betId = bet_id;
    replace_instr.newPrice = new_bet_price;

    std::vector<BetfairAPI::BettingType::ReplaceInstruction> instructions = { replace_instr };

    auto response = manager.replaceOrders(market_id, instructions);

    std::cout << response << "\n";

    auto check = manager.getCurrentOrders();

    std::cout << "Check current orders\n"; 
    printVector(check);
    return 0;
}
