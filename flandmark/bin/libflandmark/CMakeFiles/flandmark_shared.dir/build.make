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
include libflandmark/CMakeFiles/flandmark_shared.dir/depend.make

# Include the progress variables for this target.
include libflandmark/CMakeFiles/flandmark_shared.dir/progress.make

# Include the compile flags for this target's objects.
include libflandmark/CMakeFiles/flandmark_shared.dir/flags.make

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o: libflandmark/CMakeFiles/flandmark_shared.dir/flags.make
libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o: /home/ivust/facedetect/flandmark/cpp/libflandmark/flandmark_detector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivust/facedetect/flandmark/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/flandmark_shared.dir/flandmark_detector.o -c /home/ivust/facedetect/flandmark/cpp/libflandmark/flandmark_detector.cpp

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flandmark_shared.dir/flandmark_detector.i"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivust/facedetect/flandmark/cpp/libflandmark/flandmark_detector.cpp > CMakeFiles/flandmark_shared.dir/flandmark_detector.i

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flandmark_shared.dir/flandmark_detector.s"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivust/facedetect/flandmark/cpp/libflandmark/flandmark_detector.cpp -o CMakeFiles/flandmark_shared.dir/flandmark_detector.s

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.requires:
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.requires

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.provides: libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.requires
	$(MAKE) -f libflandmark/CMakeFiles/flandmark_shared.dir/build.make libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.provides.build
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.provides

libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.provides.build: libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o: libflandmark/CMakeFiles/flandmark_shared.dir/flags.make
libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o: /home/ivust/facedetect/flandmark/cpp/libflandmark/liblbp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ivust/facedetect/flandmark/bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/flandmark_shared.dir/liblbp.o -c /home/ivust/facedetect/flandmark/cpp/libflandmark/liblbp.cpp

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flandmark_shared.dir/liblbp.i"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ivust/facedetect/flandmark/cpp/libflandmark/liblbp.cpp > CMakeFiles/flandmark_shared.dir/liblbp.i

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flandmark_shared.dir/liblbp.s"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ivust/facedetect/flandmark/cpp/libflandmark/liblbp.cpp -o CMakeFiles/flandmark_shared.dir/liblbp.s

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.requires:
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.requires

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.provides: libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.requires
	$(MAKE) -f libflandmark/CMakeFiles/flandmark_shared.dir/build.make libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.provides.build
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.provides

libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.provides.build: libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o

# Object files for target flandmark_shared
flandmark_shared_OBJECTS = \
"CMakeFiles/flandmark_shared.dir/flandmark_detector.o" \
"CMakeFiles/flandmark_shared.dir/liblbp.o"

# External object files for target flandmark_shared
flandmark_shared_EXTERNAL_OBJECTS =

libflandmark/libflandmark_shared.so: libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o
libflandmark/libflandmark_shared.so: libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o
libflandmark/libflandmark_shared.so: libflandmark/CMakeFiles/flandmark_shared.dir/build.make
libflandmark/libflandmark_shared.so: libflandmark/CMakeFiles/flandmark_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libflandmark_shared.so"
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flandmark_shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libflandmark/CMakeFiles/flandmark_shared.dir/build: libflandmark/libflandmark_shared.so
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/build

libflandmark/CMakeFiles/flandmark_shared.dir/requires: libflandmark/CMakeFiles/flandmark_shared.dir/flandmark_detector.o.requires
libflandmark/CMakeFiles/flandmark_shared.dir/requires: libflandmark/CMakeFiles/flandmark_shared.dir/liblbp.o.requires
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/requires

libflandmark/CMakeFiles/flandmark_shared.dir/clean:
	cd /home/ivust/facedetect/flandmark/bin/libflandmark && $(CMAKE_COMMAND) -P CMakeFiles/flandmark_shared.dir/cmake_clean.cmake
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/clean

libflandmark/CMakeFiles/flandmark_shared.dir/depend:
	cd /home/ivust/facedetect/flandmark/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivust/facedetect/flandmark/cpp /home/ivust/facedetect/flandmark/cpp/libflandmark /home/ivust/facedetect/flandmark/bin /home/ivust/facedetect/flandmark/bin/libflandmark /home/ivust/facedetect/flandmark/bin/libflandmark/CMakeFiles/flandmark_shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libflandmark/CMakeFiles/flandmark_shared.dir/depend

