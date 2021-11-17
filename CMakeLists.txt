cmake_minimum_required(VERSION 3.10)
project(TREADLESS-LAB)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
include_directories(include)
add_executable(input 
src/vCAN_Writer.cpp 
src/socketcan_cpp.cpp 
src/wh.cpp
src/input.cpp)

target_link_libraries(input -lncurses)

add_executable(emu
src/driveline_emulator.cpp
src/wh.cpp
src/vCAN_Writer.cpp 
src/socketcan_cpp.cpp )

target_link_libraries(emu -lpthread)

