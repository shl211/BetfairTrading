file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(Logging STATIC
    ${SOURCES}
)

target_include_directories(Logging
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)