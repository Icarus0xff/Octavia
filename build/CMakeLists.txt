cmake_minimum_required(VERSION 2.8)
project(Cmodel)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_C_FLAGS "-std=c++11")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11")

aux_source_directory(../Src/ SRC_LIST)
add_executable(cmodel ${SRC_LIST})
