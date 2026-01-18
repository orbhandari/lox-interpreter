add_library(typing STATIC
    token.h
    tokentypes.h 
    types.h
)

target_include_directories(parser PUBLIC ${CMAKE_SOURCE_DIR})
