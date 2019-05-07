cmake_minimum_required(VERSION 3.14)
project(client)

set(CMAKE_CXX_STANDARD 11)

add_executable(client main.cpp TCPClient.cpp TCPClient.h)