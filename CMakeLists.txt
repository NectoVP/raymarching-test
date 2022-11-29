cmake_minimum_required(VERSION 3.25.0)

project(Tiles)

find_package(SFML COMPONENTS graphics window system REQUIRED)

set(SOURCES main.cpp)

add_executable(Tiles ${SOURCES})

target_link_libraries(Tiles sfml-graphics sfml-window sfml-system)

set_target_properties(Tiles PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
