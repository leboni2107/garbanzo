cmake_minimum_required(VERSION 4.1)
project(garbanzo)

set(CMAKE_CXX_STANDARD 26)

add_executable(garbanzo main.cpp
        src/Arguments.cpp
        include/Arguments.h)
