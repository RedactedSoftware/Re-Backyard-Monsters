cmake_minimum_required(VERSION 3.18)
project(Experiment)

set(CMAKE_CXX_STANDARD 17)

add_executable(Experiment main.cpp class/gameTick.hpp class/frameRender.hpp class/globals.hpp class/keyInput.hpp)
target_link_libraries(Experiment PUBLIC SDL2)