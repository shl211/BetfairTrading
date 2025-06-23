#pragma once
#include <string_view>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "utils/response.h"

namespace BetfairAPI {
    enum class Wallet {
        UK,
    };
    constexpr std::string_view walletToString(Wallet w) {
        switch(w) {
            case Wallet::UK: return "UK";
            default: return "UNKNOWN"; 
        }
    }

    BetfairAPI::Utils::Response getAccountFunds(std::string application_token,std::string session_token,Wallet wallet=Wallet::UK);
}

