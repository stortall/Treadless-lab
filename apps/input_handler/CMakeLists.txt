cmake_minimum_required(VERSION 3.10)

include_directories(include)
include_directories(../../libs/include)


add_executable(input src/main.cpp)

target_link_libraries(input  can_lib ncurses)