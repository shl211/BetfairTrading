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

# Fetch Boost.asio but asio standalone
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-28-0  # Or latest
)

# Fetch ImGui 
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG docking  # or master
)

# Fetch ImPlot for plotting with ImGui
FetchContent_Declare(
  implot
  GIT_REPOSITORY https://github.com/epezent/implot.git
  GIT_TAG master
)

# Enable OpenGL support for SDL3 before FetchContent_MakeAvailable
set(SDL_VIDEO_OPENGL ON CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL_GLX ON CACHE BOOL "" FORCE)
set(SDL_VIDEO_RENDER_OGL ON CACHE BOOL "" FORCE)

# Fetch SDL3 platform backend for ImGui
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.0  # or latest stable
)

# Download and make available
FetchContent_MakeAvailable(cpr json googletest magic_enum date spdlog asio imgui implot SDL3)

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

##################################
# GUI
##################################
find_package(OpenGL REQUIRED)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    # SDL3 + OpenGL3 backends
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${SDL3_SOURCE_DIR}/include
)

add_executable(gui gui.cpp)
target_link_libraries(gui 
    PRIVATE 
        BetfairAPI 
        imgui
        SDL3::SDL3
        OpenGL::GL
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