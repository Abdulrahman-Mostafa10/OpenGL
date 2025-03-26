# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/amostafa/CMP/OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amostafa/CMP/OpenGL/build

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include vendor/glfw/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/glfw/src/CMakeFiles/update_mappings.dir/progress.make

vendor/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/amostafa/CMP/OpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd /home/amostafa/CMP/OpenGL/vendor/glfw/src && /usr/bin/cmake -P /home/amostafa/CMP/OpenGL/vendor/glfw/CMake/GenerateMappings.cmake mappings.h.in mappings.h

update_mappings: vendor/glfw/src/CMakeFiles/update_mappings
update_mappings: vendor/glfw/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
vendor/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : vendor/glfw/src/CMakeFiles/update_mappings.dir/build

vendor/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd /home/amostafa/CMP/OpenGL/build/vendor/glfw/src && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : vendor/glfw/src/CMakeFiles/update_mappings.dir/clean

vendor/glfw/src/CMakeFiles/update_mappings.dir/depend:
	cd /home/amostafa/CMP/OpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amostafa/CMP/OpenGL /home/amostafa/CMP/OpenGL/vendor/glfw/src /home/amostafa/CMP/OpenGL/build /home/amostafa/CMP/OpenGL/build/vendor/glfw/src /home/amostafa/CMP/OpenGL/build/vendor/glfw/src/CMakeFiles/update_mappings.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : vendor/glfw/src/CMakeFiles/update_mappings.dir/depend

