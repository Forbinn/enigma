set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)
include_directories(${enigma_SOURCE_DIR}/src
                    ${benchmark_INCLUDE_DIRS})

add_executable(enigma_benchmark
  main.cpp
  BenchRotor.cpp
  BenchRotor.hpp
  BenchRotors.cpp
  BenchRotors.hpp
  BenchPlugBoard.cpp
  BenchPlugBoard.hpp
  BenchMachine.cpp
  BenchMachine.hpp
)

target_link_libraries(enigma_benchmark enigma
                      ${benchmark_LIBS})
if (UNIX)
    target_link_libraries(enigma_benchmark pthread)
endif()
