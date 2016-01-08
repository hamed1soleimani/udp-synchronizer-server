cmake_minimum_required(VERSION 2.8)
project(ZaeimCo_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

find_package (Threads)

set(SOURCE_FILES main.cpp UDPServer.cpp UDPServer.h utils.cpp utils.h)
add_executable(ZaeimCo_Server ${SOURCE_FILES})

target_link_libraries( ZaeimCo_Server ${Boost_LIBRARIES} )
target_link_libraries (ZaeimCo_Server ${CMAKE_THREAD_LIBS_INIT})
