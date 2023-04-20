cmake_minimum_required(VERSION 3.18)
project(Experiment)

set(CMAKE_CXX_STANDARD 20)

add_executable(Experiment src/main.cpp src/gameTick.hpp src/frameRender.hpp src/globals.hpp src/inputHandler.hpp src/gameState.hpp src/entity.hpp src/renderLayers/hud.hpp src/renderLayers/buildings.hpp)
target_link_libraries(Experiment PUBLIC SDL2)