add_library(BetfairAPI STATIC
    AccountAPI.cpp
    BettingAPI.cpp
    LoginAPI.cpp
    Response.cpp
    BetfairManager.cpp
    MarketFilter.cpp
    EventTypeResult.cpp
    CompetitionResult.cpp
    TimeRangeResult.cpp
    EventTypeIds.hpp
    MarketBettingType.hpp
    OrderStatus.hpp
    TimeGranularity.hpp
)

target_link_libraries(BetfairAPI PRIVATE cpr::cpr nlohmann_json::nlohmann_json)