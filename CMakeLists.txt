cmake_minimum_required(VERSION 3.13)
project(regex)

set(CMAKE_CXX_STANDARD 17)

add_executable(regex src/main.cc)

add_executable(tests
    tests/main.cc
    tests/catch.hpp
    tests/parser/lexer.cc)
target_include_directories(tests PUBLIC tests)

add_subdirectory(src/parser)
target_link_libraries(regex PRIVATE parser)
target_link_libraries(tests PRIVATE parser)