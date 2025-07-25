#pragma once

#include <vector>
#include "BetfairAPI/account_type/statement_item.h"

namespace BetfairAPI::AccountType {
    struct AccountStatementReport {
        std::vector<StatementItem> accountStatement;
        bool moreAvailable = false;
    };

    inline bool operator==(const AccountStatementReport& lhs, const AccountStatementReport& rhs) {
        return lhs.accountStatement == rhs.accountStatement && lhs.moreAvailable == rhs.moreAvailable;
    }

    inline bool operator!=(const AccountStatementReport& lhs, const AccountStatementReport& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const AccountStatementReport& report) {
        os << "AccountStatementReport{accountStatement=[";
        for (size_t i = 0; i < report.accountStatement.size(); ++i) {
            os << report.accountStatement[i];
            if (i + 1 < report.accountStatement.size()) os << ", ";
        }
        os << "], moreAvailable=" << std::boolalpha << report.moreAvailable << "}";
        return os;
    }
}