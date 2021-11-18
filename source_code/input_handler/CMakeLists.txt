cmake_minimum_required(VERSION 3.10)
project(inputHandler)
include_directories(include ../utils/include)

add_executable(input_handler    src/input_handler_main.cpp)

target_link_libraries(input_handler -lncurses can_lib)
