#ifndef ORDER_STATUS_HPP
#define ORDER_STATUS_HPP

#include <string_view>

namespace BetfairAPI {
    //order important -> same as in documentation
    enum class OrderStatus {
        PENDING,
        EXECUTION_COMPLETE,
        EXECUTABLE,
        EXPIRED,
    };
}

#endif