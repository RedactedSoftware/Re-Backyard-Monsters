cmake_minimum_required(VERSION 3.18)
project(ReBackyardMonsters)

file(GLOB SOURCES src/*.cpp)

include_directories(include)
add_library(ReBackyardMonsters SHARED ${SOURCES})

set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")
set(CMAKE_CXX_STANDARD 20)

install(TARGETS ReBackyardMonsters DESTINATION lib/ReBackyardMonsters)

file(GLOB HEADERS include/*.hpp)
install(FILES ${HEADERS} DESTINATION include/ReBackyardMonsters)

add_executable(Executable src/main.cpp)
target_link_libraries(Executable PUBLIC ReBackyardMonsters SDL2 SDL2_image)