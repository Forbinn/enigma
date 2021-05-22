set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cppunit REQUIRED)
include_directories(${enigma_SOURCE_DIR}/src
                    ${cppunit_INCLUDE_DIRS})

add_executable(enigma_unit_test
  main.cpp
  TestRotor.cpp
  TestRotor.hpp
  TestReflector.cpp
  TestReflector.hpp
  TestPlugBoard.cpp
  TestPlugBoard.hpp
  TestRotors.cpp
  TestRotors.hpp
  TestMachine.cpp
  TestMachine.hpp
)

target_link_libraries(enigma_unit_test enigma
                      ${cppunit_LIBS})

add_test(NAME test COMMAND enigma_unit_test)
