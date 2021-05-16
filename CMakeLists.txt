cmake_minimum_required(VERSION 3.14)
project(enigma LANGUAGES CXX)

add_subdirectory(src)

if (ENIGMA_TESTS)
    enable_testing()
    add_subdirectory(unit_tests)
endif()

if (ENIGMA_BENCHMARK)
    add_subdirectory(benchmark)
endif()
