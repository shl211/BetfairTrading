file(GLOB SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)

add_library(Logging STATIC
    ${SOURCES}
)

target_include_directories(Logging
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)