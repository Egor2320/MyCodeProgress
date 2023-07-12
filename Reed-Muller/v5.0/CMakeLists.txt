cmake_minimum_required(VERSION 3.24)
project(Reed_Muller)

set(CMAKE_CXX_STANDARD 17)

add_executable(Reed_Muller main.cpp helper.cpp helper.h reed_muller.cpp reed_muller.h test.cpp test.h)