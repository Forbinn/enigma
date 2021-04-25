cmake_minimum_required(VERSION 3.14)

project(enigma LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(enigma SHARED
  enigma_global.hpp
  Rotor.hpp
  Rotor.cpp
  PlugBoard.cpp
  PlugBoard.hpp
  Reflector.hpp
)

target_compile_definitions(enigma PRIVATE ENIGMA_LIBRARY)
