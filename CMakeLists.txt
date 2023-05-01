cmake_minimum_required(VERSION 3.18)
project(ReBackyardMonsters)

file(GLOB SOURCES src/*.cpp)

include_directories(include)
add_library(${PROJECT_NAME} SHARED ${SOURCES} src/gameState.hpp src/bank.hpp)

set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")
set(CMAKE_CXX_STANDARD 20)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

file(GLOB HEADERS include/*.hpp)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

add_executable(Executable src/main.cpp src/bank.hpp)
target_link_libraries(Executable PUBLIC ReBackyardMonsters SDL2 SDL2_image)