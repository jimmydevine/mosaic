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
CMAKE_SOURCE_DIR = /home/jiffe/mosaic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiffe/mosaic/build

# Include any dependencies generated for this target.
include submodules/backward-cpp/CMakeFiles/backward.dir/depend.make

# Include the progress variables for this target.
include submodules/backward-cpp/CMakeFiles/backward.dir/progress.make

# Include the compile flags for this target's objects.
include submodules/backward-cpp/CMakeFiles/backward.dir/flags.make

submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.o: submodules/backward-cpp/CMakeFiles/backward.dir/flags.make
submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.o: ../submodules/backward-cpp/backward.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiffe/mosaic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.o"
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backward.dir/backward.cpp.o -c /home/jiffe/mosaic/submodules/backward-cpp/backward.cpp

submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backward.dir/backward.cpp.i"
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiffe/mosaic/submodules/backward-cpp/backward.cpp > CMakeFiles/backward.dir/backward.cpp.i

submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backward.dir/backward.cpp.s"
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiffe/mosaic/submodules/backward-cpp/backward.cpp -o CMakeFiles/backward.dir/backward.cpp.s

# Object files for target backward
backward_OBJECTS = \
"CMakeFiles/backward.dir/backward.cpp.o"

# External object files for target backward
backward_EXTERNAL_OBJECTS =

submodules/backward-cpp/libbackward.a: submodules/backward-cpp/CMakeFiles/backward.dir/backward.cpp.o
submodules/backward-cpp/libbackward.a: submodules/backward-cpp/CMakeFiles/backward.dir/build.make
submodules/backward-cpp/libbackward.a: submodules/backward-cpp/CMakeFiles/backward.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiffe/mosaic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbackward.a"
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && $(CMAKE_COMMAND) -P CMakeFiles/backward.dir/cmake_clean_target.cmake
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backward.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
submodules/backward-cpp/CMakeFiles/backward.dir/build: submodules/backward-cpp/libbackward.a

.PHONY : submodules/backward-cpp/CMakeFiles/backward.dir/build

submodules/backward-cpp/CMakeFiles/backward.dir/clean:
	cd /home/jiffe/mosaic/build/submodules/backward-cpp && $(CMAKE_COMMAND) -P CMakeFiles/backward.dir/cmake_clean.cmake
.PHONY : submodules/backward-cpp/CMakeFiles/backward.dir/clean

submodules/backward-cpp/CMakeFiles/backward.dir/depend:
	cd /home/jiffe/mosaic/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiffe/mosaic /home/jiffe/mosaic/submodules/backward-cpp /home/jiffe/mosaic/build /home/jiffe/mosaic/build/submodules/backward-cpp /home/jiffe/mosaic/build/submodules/backward-cpp/CMakeFiles/backward.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : submodules/backward-cpp/CMakeFiles/backward.dir/depend

