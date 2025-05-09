add_library(BetfairAPI STATIC
    AccountsAPI.cpp
    LoginAPI.cpp
    Response.cpp
)

target_link_libraries(BetfairAPI PRIVATE cpr::cpr nlohmann_json::nlohmann_json)