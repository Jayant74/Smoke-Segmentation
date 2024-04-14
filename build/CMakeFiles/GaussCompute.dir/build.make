# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jayant/workspace/Smoke-Segmentation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jayant/workspace/Smoke-Segmentation/build

# Include any dependencies generated for this target.
include CMakeFiles/GaussCompute.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GaussCompute.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GaussCompute.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GaussCompute.dir/flags.make

CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o: CMakeFiles/GaussCompute.dir/flags.make
CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o: ../GaussToolKit/GaussCompute.cpp
CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o: CMakeFiles/GaussCompute.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jayant/workspace/Smoke-Segmentation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o -MF CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o.d -o CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o -c /home/jayant/workspace/Smoke-Segmentation/GaussToolKit/GaussCompute.cpp

CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jayant/workspace/Smoke-Segmentation/GaussToolKit/GaussCompute.cpp > CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.i

CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jayant/workspace/Smoke-Segmentation/GaussToolKit/GaussCompute.cpp -o CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.s

# Object files for target GaussCompute
GaussCompute_OBJECTS = \
"CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o"

# External object files for target GaussCompute
GaussCompute_EXTERNAL_OBJECTS =

libGaussCompute.a: CMakeFiles/GaussCompute.dir/GaussToolKit/GaussCompute.cpp.o
libGaussCompute.a: CMakeFiles/GaussCompute.dir/build.make
libGaussCompute.a: CMakeFiles/GaussCompute.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jayant/workspace/Smoke-Segmentation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGaussCompute.a"
	$(CMAKE_COMMAND) -P CMakeFiles/GaussCompute.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GaussCompute.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GaussCompute.dir/build: libGaussCompute.a
.PHONY : CMakeFiles/GaussCompute.dir/build

CMakeFiles/GaussCompute.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GaussCompute.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GaussCompute.dir/clean

CMakeFiles/GaussCompute.dir/depend:
	cd /home/jayant/workspace/Smoke-Segmentation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jayant/workspace/Smoke-Segmentation /home/jayant/workspace/Smoke-Segmentation /home/jayant/workspace/Smoke-Segmentation/build /home/jayant/workspace/Smoke-Segmentation/build /home/jayant/workspace/Smoke-Segmentation/build/CMakeFiles/GaussCompute.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GaussCompute.dir/depend

