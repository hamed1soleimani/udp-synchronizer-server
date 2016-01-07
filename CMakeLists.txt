cmake_minimum_required(VERSION 3.3)
project(ZaeimC0_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ZaeimC0_Server ${SOURCE_FILES})