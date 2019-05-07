cmake_minimum_required(VERSION 3.14)
project(server)

set(CMAKE_CXX_STANDARD 11)

add_executable(server main.cpp ScriptLauncher.cpp ScriptLauncher.h TCPServer.cpp TCPServer.h)

TARGET_LINK_LIBRARIES(server pthread)
