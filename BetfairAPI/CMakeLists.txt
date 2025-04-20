add_library(BetfairAPI STATIC
    AccountsAPI.cpp
)

target_link_libraries(BetfairAPI PRIVATE cpr::cpr)