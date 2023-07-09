cmake_minimum_required(VERSION 3.24)
project(Reed_Muller)

set(CMAKE_CXX_STANDARD 17)

add_executable(Reed_Muller main.cpp logical_function.cpp logical_function.h popcounter.cpp popcounter.h)
