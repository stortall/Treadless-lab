cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(include)
add_library(can_lib STATIC src/read_write_handler.cpp src/socketcan.cpp )

set_target_properties(can_lib

PROPERTIES

ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"

LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"

RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"

)