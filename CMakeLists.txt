cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_CXX_STANDARD 20)

add_executable(game main.c)

target_link_libraries(game -lopengl32 -lglew32 -lfreeglut -lglu32)