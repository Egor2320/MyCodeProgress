cmake_minimum_required(VERSION 3.24)
project(Reed_Muller)

set(CMAKE_CXX_STANDARD 17)

add_executable(Reed_Muller main.cpp Popcounter.cpp Popcounter.h LogicalFunction.cpp LogicalFunction.h Test.cpp Test.h)