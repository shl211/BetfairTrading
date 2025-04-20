add_library(BetfairAPI STATIC
    AccountsAPI.cpp
    LoginAPI.cpp
)

target_link_libraries(BetfairAPI PRIVATE cpr::cpr)