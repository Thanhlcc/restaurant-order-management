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
CMAKE_SOURCE_DIR = /home/thanhle1102/C++/DSA/huffman_coding_tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl

# Include any dependencies generated for this target.
include CMakeFiles/huffman_coding_tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/huffman_coding_tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/huffman_coding_tree.dir/flags.make

CMakeFiles/huffman_coding_tree.dir/main.cpp.o: CMakeFiles/huffman_coding_tree.dir/flags.make
CMakeFiles/huffman_coding_tree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/huffman_coding_tree.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/huffman_coding_tree.dir/main.cpp.o -c /home/thanhle1102/C++/DSA/huffman_coding_tree/main.cpp

CMakeFiles/huffman_coding_tree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/huffman_coding_tree.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thanhle1102/C++/DSA/huffman_coding_tree/main.cpp > CMakeFiles/huffman_coding_tree.dir/main.cpp.i

CMakeFiles/huffman_coding_tree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/huffman_coding_tree.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thanhle1102/C++/DSA/huffman_coding_tree/main.cpp -o CMakeFiles/huffman_coding_tree.dir/main.cpp.s

# Object files for target huffman_coding_tree
huffman_coding_tree_OBJECTS = \
"CMakeFiles/huffman_coding_tree.dir/main.cpp.o"

# External object files for target huffman_coding_tree
huffman_coding_tree_EXTERNAL_OBJECTS =

huffman_coding_tree: CMakeFiles/huffman_coding_tree.dir/main.cpp.o
huffman_coding_tree: CMakeFiles/huffman_coding_tree.dir/build.make
huffman_coding_tree: CMakeFiles/huffman_coding_tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable huffman_coding_tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/huffman_coding_tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/huffman_coding_tree.dir/build: huffman_coding_tree

.PHONY : CMakeFiles/huffman_coding_tree.dir/build

CMakeFiles/huffman_coding_tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/huffman_coding_tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/huffman_coding_tree.dir/clean

CMakeFiles/huffman_coding_tree.dir/depend:
	cd /home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thanhle1102/C++/DSA/huffman_coding_tree /home/thanhle1102/C++/DSA/huffman_coding_tree /home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl /home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl /home/thanhle1102/C++/DSA/huffman_coding_tree/cmake-build-debug-wsl/CMakeFiles/huffman_coding_tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/huffman_coding_tree.dir/depend

