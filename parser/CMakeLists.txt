add_library(parser STATIC
    parser.h
)

target_include_directories(parser PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parser PUBLIC ast lexer)
