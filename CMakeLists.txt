cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_CXX_STANDARD 20)

add_executable(game main.c gameBoard.h color.h gameBoard.c color.c character.c character.h configs.h configs.c text.c text.h)

target_link_libraries(game -lopengl32 -lglew32 -lfreeglut -lglu32)