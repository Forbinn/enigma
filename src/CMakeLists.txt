set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(enigma
  enigma_global.hpp
  Rotor.cpp
  Rotor.hpp
  PlugBoard.cpp
  PlugBoard.hpp
  Reflector.cpp
  Reflector.hpp
  Rotors.cpp
  Rotors.hpp
  Machine.cpp
  Machine.hpp
)

target_compile_definitions(enigma PRIVATE ENIGMA_LIBRARY)
