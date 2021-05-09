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
)

target_link_libraries(enigma_unit_test enigma
                      ${cppunit_LIBS})

add_test(NAME test COMMAND enigma_unit_test)
