cmake_minimum_required (VERSION 3.8)

project ("shadowanthems")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

ADD_DEFINITIONS(-D ASIO_STANDALONE)

set(ASIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/asio/asio CACHE STRING "asio dir")
set(SHADOW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shadow CACHE STRING "shadow dir")
set(THIRD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party CACHE STRING "third_party dir")


if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif (UNIX)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")
endif(APPLE)

add_subdirectory ("shadow")
add_subdirectory ("server")