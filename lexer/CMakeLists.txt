add_library(lexer STATIC
    lexer.cpp
    lexer.h
)

target_include_directories(lexer PUBLIC ${CMAKE_SOURCE_DIR})
