cmake_minimum_required(VERSION 3.5)

project(qenigma LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(enigma)

set(PROJECT_SOURCES
        main.cpp
        Widget.cpp
        Widget.hpp
        Widget.ui
)

add_executable(qenigma
    ${PROJECT_SOURCES}
)

target_link_libraries(qenigma PRIVATE Qt5::Widgets enigma)
