add_library(ast STATIC
    astPrinter.cpp
    astPrinter.h
    trees.h
)

target_include_directories(ast PUBLIC ${CMAKE_SOURCE_DIR})
