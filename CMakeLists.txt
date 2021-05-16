cmake_minimum_required(VERSION 3.14)
project(enigma LANGUAGES CXX)

add_subdirectory(src)

set(ENIGMA_TESTS ON CACHE BOOL "Compile and run unit-tests. Requires cppunit")
set(ENIGMA_BENCHMARK OFF CACHE BOOL "Compile and run benchmark. Requires google-benchmark")

if (ENIGMA_TESTS)
    enable_testing()
    add_subdirectory(unit_tests)
endif()

if (ENIGMA_BENCHMARK)
    add_subdirectory(benchmark)
endif()
