cmake_minimum_required(VERSION 3.10)

include_directories(include)
include_directories(../../libs/include)


add_executable(input src/main.cpp)

target_link_libraries(input  can_lib ncurses)

set_target_properties(input

PROPERTIES

ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"

LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"

RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"

)