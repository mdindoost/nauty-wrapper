# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /scratch/shared/apps/cmake/bin/cmake

# The command to remove a file.
RM = /scratch/shared/apps/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /scratch/users/md724/nauty-wrapper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /scratch/users/md724/nauty-wrapper/build

# Utility rule file for nauty_build.

# Include any custom commands dependencies for this target.
include CMakeFiles/nauty_build.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nauty_build.dir/progress.make

CMakeFiles/nauty_build:
	cd /scratch/users/md724/nauty-wrapper/external/nauty2_8_9 && ./configure
	cd /scratch/users/md724/nauty-wrapper/external/nauty2_8_9 && make

nauty_build: CMakeFiles/nauty_build
nauty_build: CMakeFiles/nauty_build.dir/build.make
.PHONY : nauty_build

# Rule to build all files generated by this target.
CMakeFiles/nauty_build.dir/build: nauty_build
.PHONY : CMakeFiles/nauty_build.dir/build

CMakeFiles/nauty_build.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nauty_build.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nauty_build.dir/clean

CMakeFiles/nauty_build.dir/depend:
	cd /scratch/users/md724/nauty-wrapper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /scratch/users/md724/nauty-wrapper /scratch/users/md724/nauty-wrapper /scratch/users/md724/nauty-wrapper/build /scratch/users/md724/nauty-wrapper/build /scratch/users/md724/nauty-wrapper/build/CMakeFiles/nauty_build.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nauty_build.dir/depend

