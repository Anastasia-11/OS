cmake_minimum_required(VERSION 3.17)
project(OS_lab1_linux)

set(CMAKE_CXX_STANDARD 20)

add_library(NUMBER_LIB STATIC Number.cpp Number.h)
add_library(VECTOR_LIB SHARED Vector.cpp Vector.h)

add_executable(Main main.cpp)

target_link_libraries(Main PRIVATE NUMBER_LIB)
target_link_libraries(VECTOR_LIB PRIVATE NUMBER_LIB)
target_link_libraries(Main PRIVATE VECTOR_LIB)