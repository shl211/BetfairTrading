#pragma once

#include <string>
#include <optional>
#include <ostream>
#include "BetfairAPI/date.h"
#include "BetfairAPI/account_enum/item_class.hpp"
#include <map>

namespace BetfairAPI::AccountType {
    struct StatementItem {
        std::string refId;
        std::optional<Date> itemDate;
        std::optional<double> amount;
        std::optional<double> balance;
        std::optional<AccountEnum::ItemClass> itemClass;
        std::map<std::string,std::string> itemClassData;
    };

    inline bool operator==(const StatementItem& lhs, const StatementItem& rhs) {
        return lhs.refId == rhs.refId &&
               lhs.itemDate == rhs.itemDate &&
               lhs.amount == rhs.amount &&
               lhs.balance == rhs.balance &&
               lhs.itemClass == rhs.itemClass &&
               lhs.itemClassData == rhs.itemClassData;
    }

    inline bool operator!=(const StatementItem& lhs, const StatementItem& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const StatementItem& item) {
        os << "StatementItem{refId=" << item.refId;
        os << ", itemDate=";
        if (item.itemDate) os << item.itemDate->getIsoString(); else os << "null";
        os << ", amount=";
        if (item.amount) os << *item.amount; else os << "null";
        os << ", balance=";
        if (item.balance) os << *item.balance; else os << "null";
        os << ", itemClass=";
        if (item.itemClass) os << static_cast<int>(*item.itemClass); else os << "null";
        os << ", itemClassData={";
        bool first = true;
        for (const auto& [k, v] : item.itemClassData) {
            if (!first) os << ", ";
            os << k << ":" << v;
            first = false;
        }
        os << "}}";
        return os;
    }
}