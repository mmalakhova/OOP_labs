cmake_minimum_required(VERSION 3.17)
project(game_of_life)

set(CMAKE_CXX_STANDARD 14)

add_executable(game_of_life main.cpp game_board.cpp game_board.h parser.cpp parser.h console.cpp console.h)