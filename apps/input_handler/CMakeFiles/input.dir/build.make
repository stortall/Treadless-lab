# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ptyagi1/projects/CAN/CAN/Treadless-lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ptyagi1/projects/CAN/CAN/Treadless-lab

# Include any dependencies generated for this target.
include apps/input_handler/CMakeFiles/input.dir/depend.make

# Include the progress variables for this target.
include apps/input_handler/CMakeFiles/input.dir/progress.make

# Include the compile flags for this target's objects.
include apps/input_handler/CMakeFiles/input.dir/flags.make

apps/input_handler/CMakeFiles/input.dir/src/main.cpp.o: apps/input_handler/CMakeFiles/input.dir/flags.make
apps/input_handler/CMakeFiles/input.dir/src/main.cpp.o: apps/input_handler/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ptyagi1/projects/CAN/CAN/Treadless-lab/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/input_handler/CMakeFiles/input.dir/src/main.cpp.o"
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/input.dir/src/main.cpp.o -c /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler/src/main.cpp

apps/input_handler/CMakeFiles/input.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/input.dir/src/main.cpp.i"
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler/src/main.cpp > CMakeFiles/input.dir/src/main.cpp.i

apps/input_handler/CMakeFiles/input.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/input.dir/src/main.cpp.s"
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler/src/main.cpp -o CMakeFiles/input.dir/src/main.cpp.s

# Object files for target input
input_OBJECTS = \
"CMakeFiles/input.dir/src/main.cpp.o"

# External object files for target input
input_EXTERNAL_OBJECTS =

apps/input_handler/input: apps/input_handler/CMakeFiles/input.dir/src/main.cpp.o
apps/input_handler/input: apps/input_handler/CMakeFiles/input.dir/build.make
apps/input_handler/input: libs/libcan_lib.a
apps/input_handler/input: apps/input_handler/CMakeFiles/input.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ptyagi1/projects/CAN/CAN/Treadless-lab/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable input"
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/input.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/input_handler/CMakeFiles/input.dir/build: apps/input_handler/input

.PHONY : apps/input_handler/CMakeFiles/input.dir/build

apps/input_handler/CMakeFiles/input.dir/clean:
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler && $(CMAKE_COMMAND) -P CMakeFiles/input.dir/cmake_clean.cmake
.PHONY : apps/input_handler/CMakeFiles/input.dir/clean

apps/input_handler/CMakeFiles/input.dir/depend:
	cd /home/ptyagi1/projects/CAN/CAN/Treadless-lab && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ptyagi1/projects/CAN/CAN/Treadless-lab /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler /home/ptyagi1/projects/CAN/CAN/Treadless-lab /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler /home/ptyagi1/projects/CAN/CAN/Treadless-lab/apps/input_handler/CMakeFiles/input.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/input_handler/CMakeFiles/input.dir/depend

