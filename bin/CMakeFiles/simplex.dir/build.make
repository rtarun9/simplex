# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Tarun\Desktop\Projects\GP\simplex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Tarun\Desktop\Projects\GP\simplex\bin

# Include any dependencies generated for this target.
include CMakeFiles/simplex.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simplex.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simplex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simplex.dir/flags.make

CMakeFiles/simplex.dir/src/main.cpp.obj: CMakeFiles/simplex.dir/flags.make
CMakeFiles/simplex.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/simplex.dir/src/main.cpp.obj: CMakeFiles/simplex.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Tarun\Desktop\Projects\GP\simplex\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simplex.dir/src/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/simplex.dir/src/main.cpp.obj -MF CMakeFiles\simplex.dir\src\main.cpp.obj.d -o CMakeFiles\simplex.dir\src\main.cpp.obj -c C:\Users\Tarun\Desktop\Projects\GP\simplex\src\main.cpp

CMakeFiles/simplex.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplex.dir/src/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Tarun\Desktop\Projects\GP\simplex\src\main.cpp > CMakeFiles\simplex.dir\src\main.cpp.i

CMakeFiles/simplex.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplex.dir/src/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Tarun\Desktop\Projects\GP\simplex\src\main.cpp -o CMakeFiles\simplex.dir\src\main.cpp.s

# Object files for target simplex
simplex_OBJECTS = \
"CMakeFiles/simplex.dir/src/main.cpp.obj"

# External object files for target simplex
simplex_EXTERNAL_OBJECTS =

simplex.exe: CMakeFiles/simplex.dir/src/main.cpp.obj
simplex.exe: CMakeFiles/simplex.dir/build.make
simplex.exe: CMakeFiles/simplex.dir/linklibs.rsp
simplex.exe: CMakeFiles/simplex.dir/objects1.rsp
simplex.exe: CMakeFiles/simplex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Tarun\Desktop\Projects\GP\simplex\bin\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable simplex.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simplex.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simplex.dir/build: simplex.exe
.PHONY : CMakeFiles/simplex.dir/build

CMakeFiles/simplex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\simplex.dir\cmake_clean.cmake
.PHONY : CMakeFiles/simplex.dir/clean

CMakeFiles/simplex.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Tarun\Desktop\Projects\GP\simplex C:\Users\Tarun\Desktop\Projects\GP\simplex C:\Users\Tarun\Desktop\Projects\GP\simplex\bin C:\Users\Tarun\Desktop\Projects\GP\simplex\bin C:\Users\Tarun\Desktop\Projects\GP\simplex\bin\CMakeFiles\simplex.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simplex.dir/depend

