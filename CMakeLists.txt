cmake_minimum_required(VERSION 3.10)
project(LoxInterpreter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for libraries
add_subdirectory(ast)
add_subdirectory(interpreter)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(tests)

# Main executable
add_executable(lox main.cpp)
target_link_libraries(lox PRIVATE interpreter lexer parser ast)