add_library(interpreter STATIC
    interpretor.cpp
    interpreter.h
)

target_include_directories(interpreter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(interpreter PUBLIC parser ast lexer)
