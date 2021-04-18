cmake_minimum_required(VERSION 3.17)
project(OS_lab3)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(OS_lab3 main.cpp Timer.cpp Timer.h Params1.cpp Params1.h Params2.cpp Params2.h Params3.cpp Params3.h)