cmake_minimum_required(VERSION 2.8)
project(UDP_Synchronizer_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

find_package(Threads)

set(SOURCE_FILES main.cpp network/UDPServer.cpp network/UDPServer.h utilities/utils.cpp utilities/utils.h data/Message.h data/Message.cpp consumer/MessageConsumer.cpp consumer/MessageConsumer.h data/Chunk.cpp data/Chunk.h consumer/ChunkConsumer.cpp consumer/ChunkConsumer.h consumer/ChunkConsumer.cpp consumer/ChunkConsumer.h)
add_executable(UDP_Synchronizer_Server ${SOURCE_FILES})

target_link_libraries(UDP_Synchronizer_Server ${Boost_LIBRARIES})
target_link_libraries(UDP_Synchronizer_Server ${CMAKE_THREAD_LIBS_INIT})
