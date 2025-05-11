cmake_minimum_required(VERSION 3.10)
project(BetfairProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###################################
# Fetch external libraries
###################################
include(FetchContent)
#Fetch CPR library
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.11.0
)

#Fetch nlohmann/json library
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2
)

#Fetch gtest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

FetchContent_MakeAvailable(cpr json googletest)
enable_testing()

add_subdirectory(BetfairAPI)

# Primary executable
add_executable(app main.cpp)
target_link_libraries(app PRIVATE BetfairAPI cpr::cpr nlohmann_json::nlohmann_json)

# Tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()