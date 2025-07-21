cmake_minimum_required(VERSION 3.10)
project(BetfairTrading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###################################
# Fetch external libraries
###################################
include(FetchContent)

# Fetch CPR
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.11.0
)

# Fetch nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2
)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# Fetch magic_enum 
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG v0.9.6
)

# Ftech Howard's date and datetime support
FetchContent_Declare(
    date
    GIT_REPOSITORY https://github.com/HowardHinnant/date.git
    GIT_TAG v3.0.4
)

# Fetch spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.13.0  # Or latest stable tag
)

# Download and make available
FetchContent_MakeAvailable(cpr json googletest magic_enum date spdlog)

###################################
# Project Targets
###################################

add_subdirectory(BetfairAPI)
add_subdirectory(Logging)

add_executable(app main.cpp)
target_link_libraries(app 
    PRIVATE 
        BetfairAPI 
)

###################################
# Enable Tests
###################################
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

##################################
# Examples
##################################
add_subdirectory(examples)