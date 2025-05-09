add_library(BetfairAPI STATIC
    AccountAPI.cpp
    BettingAPI.cpp
    LoginAPI.cpp
    Response.cpp
    BetfairManager.cpp
)

target_link_libraries(BetfairAPI PRIVATE cpr::cpr nlohmann_json::nlohmann_json)