# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ivust/facedetect/flandmark/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivust/facedetect/flandmark/bin

# Include any dependencies generated for this target.
include CMakeFiles/Project_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project_2.dir/flags.make

CMakeFiles/Project_2.dir/example2.o: CMakeFiles/Project_2.dir/flags.make
CMakeFiles/Project_2.dir/example2.o: /home/ivust/facedetect/flandmark/cpp/example2.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivust/facedetect/flandmark/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Project_2.dir/example2.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Project_2.dir/example2.o -c /home/ivust/facedetect/flandmark/cpp/example2.cpp

CMakeFiles/Project_2.dir/example2.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_2.dir/example2.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivust/facedetect/flandmark/cpp/example2.cpp > CMakeFiles/Project_2.dir/example2.i

CMakeFiles/Project_2.dir/example2.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_2.dir/example2.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivust/facedetect/flandmark/cpp/example2.cpp -o CMakeFiles/Project_2.dir/example2.s

CMakeFiles/Project_2.dir/example2.o.requires:
.PHONY : CMakeFiles/Project_2.dir/example2.o.requires

CMakeFiles/Project_2.dir/example2.o.provides: CMakeFiles/Project_2.dir/example2.o.requires
	$(MAKE) -f CMakeFiles/Project_2.dir/build.make CMakeFiles/Project_2.dir/example2.o.provides.build
.PHONY : CMakeFiles/Project_2.dir/example2.o.provides

CMakeFiles/Project_2.dir/example2.o.provides.build: CMakeFiles/Project_2.dir/example2.o

# Object files for target Project_2
Project_2_OBJECTS = \
"CMakeFiles/Project_2.dir/example2.o"

# External object files for target Project_2
Project_2_EXTERNAL_OBJECTS =

Project_2: CMakeFiles/Project_2.dir/example2.o
Project_2: CMakeFiles/Project_2.dir/build.make
Project_2: libflandmark/libflandmark_static.a
Project_2: CMakeFiles/Project_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Project_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project_2.dir/build: Project_2
.PHONY : CMakeFiles/Project_2.dir/build

CMakeFiles/Project_2.dir/requires: CMakeFiles/Project_2.dir/example2.o.requires
.PHONY : CMakeFiles/Project_2.dir/requires

CMakeFiles/Project_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project_2.dir/clean

CMakeFiles/Project_2.dir/depend:
	cd /home/ivust/facedetect/flandmark/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivust/facedetect/flandmark/cpp /home/ivust/facedetect/flandmark/cpp /home/ivust/facedetect/flandmark/bin /home/ivust/facedetect/flandmark/bin /home/ivust/facedetect/flandmark/bin/CMakeFiles/Project_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project_2.dir/depend

