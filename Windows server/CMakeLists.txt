cmake_minimum_required(VERSION 3.23)
project(Windows_server)

set(CMAKE_CXX_STANDARD 17)
link_libraries(ws2_32 wsock32)


add_executable(Windows_server
        server_windows.cpp
        http_tcpServer_windows.h
        http_tcpServer_windows.cpp)
