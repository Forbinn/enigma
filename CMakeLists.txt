cmake_minimum_required(VERSION 3.14)
project(enigma LANGUAGES CXX)

add_subdirectory(src)

enable_testing()
add_subdirectory(unit_tests)
