cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(include)
add_library(can_lib STATIC src/wh.cpp src/vCAN_Writer src/socketcan_cpp.cpp )
