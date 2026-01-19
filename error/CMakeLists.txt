add_library(error STATIC
    error.h
)

target_include_directories(error PUBLIC ${CMAKE_SOURCE_DIR})