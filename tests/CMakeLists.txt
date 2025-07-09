file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(test_suite
    ${TEST_SOURCES}
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
)

include(GoogleTest)
gtest_discover_tests(test_suite)