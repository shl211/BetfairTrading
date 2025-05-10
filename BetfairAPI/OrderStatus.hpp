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