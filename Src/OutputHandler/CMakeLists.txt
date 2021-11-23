cmake_minimum_required(VERSION 3.10)
project(InputHandler)

include_directories(include)
include_directories(../Libs/socketcan)
include_directories(../Libs/can_transmitter_receiver)

add_executable(InputHandler    
		src/input_handler_main.cpp)

target_link_libraries(input_handler -lncurses can_lib)
