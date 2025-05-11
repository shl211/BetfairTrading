add_executable(test_suite
    test_market_filter.cpp
)

target_include_directories(test_suite
    PRIVATE
        ${PROJECT_SOURCE_DIR}/BetfairAPI
)

target_link_libraries(test_suite
    PRIVATE
        gtest
        gtest_main
        BetfairAPI
        cpr::cpr
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(test_suite)