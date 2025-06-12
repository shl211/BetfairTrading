add_executable(test_suite
    test_enum_utils.cpp
)

target_include_directories(test_suite
    PRIVATE
        ${PROJECT_SOURCE_DIR}/BetfairAPI
)

target_link_libraries(test_suite
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        BetfairAPI
        cpr::cpr
        nlohmann_json::nlohmann_json
        magic_enum
)

include(GoogleTest)
gtest_discover_tests(test_suite)
