cmake_minimum_required(VERSION 3.10)

include_directories(include)
include_directories(../../libs/include)


add_executable(emu src/main.cpp src/driveline.cpp)

target_link_libraries(emu can_lib pthread)