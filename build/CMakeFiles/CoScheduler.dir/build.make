# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/gong/projects/CoScheduler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gong/projects/CoScheduler/build

# Include any dependencies generated for this target.
include CMakeFiles/CoScheduler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CoScheduler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CoScheduler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CoScheduler.dir/flags.make

CMakeFiles/CoScheduler.dir/Async.o: CMakeFiles/CoScheduler.dir/flags.make
CMakeFiles/CoScheduler.dir/Async.o: /home/gong/projects/CoScheduler/Async.cc
CMakeFiles/CoScheduler.dir/Async.o: CMakeFiles/CoScheduler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CoScheduler.dir/Async.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoScheduler.dir/Async.o -MF CMakeFiles/CoScheduler.dir/Async.o.d -o CMakeFiles/CoScheduler.dir/Async.o -c /home/gong/projects/CoScheduler/Async.cc

CMakeFiles/CoScheduler.dir/Async.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CoScheduler.dir/Async.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/CoScheduler/Async.cc > CMakeFiles/CoScheduler.dir/Async.i

CMakeFiles/CoScheduler.dir/Async.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CoScheduler.dir/Async.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/CoScheduler/Async.cc -o CMakeFiles/CoScheduler.dir/Async.s

CMakeFiles/CoScheduler.dir/BlockWait.o: CMakeFiles/CoScheduler.dir/flags.make
CMakeFiles/CoScheduler.dir/BlockWait.o: /home/gong/projects/CoScheduler/BlockWait.cc
CMakeFiles/CoScheduler.dir/BlockWait.o: CMakeFiles/CoScheduler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CoScheduler.dir/BlockWait.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoScheduler.dir/BlockWait.o -MF CMakeFiles/CoScheduler.dir/BlockWait.o.d -o CMakeFiles/CoScheduler.dir/BlockWait.o -c /home/gong/projects/CoScheduler/BlockWait.cc

CMakeFiles/CoScheduler.dir/BlockWait.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CoScheduler.dir/BlockWait.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/CoScheduler/BlockWait.cc > CMakeFiles/CoScheduler.dir/BlockWait.i

CMakeFiles/CoScheduler.dir/BlockWait.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CoScheduler.dir/BlockWait.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/CoScheduler/BlockWait.cc -o CMakeFiles/CoScheduler.dir/BlockWait.s

CMakeFiles/CoScheduler.dir/Coroutine.o: CMakeFiles/CoScheduler.dir/flags.make
CMakeFiles/CoScheduler.dir/Coroutine.o: /home/gong/projects/CoScheduler/Coroutine.cc
CMakeFiles/CoScheduler.dir/Coroutine.o: CMakeFiles/CoScheduler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CoScheduler.dir/Coroutine.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoScheduler.dir/Coroutine.o -MF CMakeFiles/CoScheduler.dir/Coroutine.o.d -o CMakeFiles/CoScheduler.dir/Coroutine.o -c /home/gong/projects/CoScheduler/Coroutine.cc

CMakeFiles/CoScheduler.dir/Coroutine.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CoScheduler.dir/Coroutine.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/CoScheduler/Coroutine.cc > CMakeFiles/CoScheduler.dir/Coroutine.i

CMakeFiles/CoScheduler.dir/Coroutine.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CoScheduler.dir/Coroutine.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/CoScheduler/Coroutine.cc -o CMakeFiles/CoScheduler.dir/Coroutine.s

CMakeFiles/CoScheduler.dir/EventScheduler.o: CMakeFiles/CoScheduler.dir/flags.make
CMakeFiles/CoScheduler.dir/EventScheduler.o: /home/gong/projects/CoScheduler/EventScheduler.cc
CMakeFiles/CoScheduler.dir/EventScheduler.o: CMakeFiles/CoScheduler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CoScheduler.dir/EventScheduler.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoScheduler.dir/EventScheduler.o -MF CMakeFiles/CoScheduler.dir/EventScheduler.o.d -o CMakeFiles/CoScheduler.dir/EventScheduler.o -c /home/gong/projects/CoScheduler/EventScheduler.cc

CMakeFiles/CoScheduler.dir/EventScheduler.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CoScheduler.dir/EventScheduler.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/CoScheduler/EventScheduler.cc > CMakeFiles/CoScheduler.dir/EventScheduler.i

CMakeFiles/CoScheduler.dir/EventScheduler.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CoScheduler.dir/EventScheduler.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/CoScheduler/EventScheduler.cc -o CMakeFiles/CoScheduler.dir/EventScheduler.s

CMakeFiles/CoScheduler.dir/main.o: CMakeFiles/CoScheduler.dir/flags.make
CMakeFiles/CoScheduler.dir/main.o: /home/gong/projects/CoScheduler/main.cc
CMakeFiles/CoScheduler.dir/main.o: CMakeFiles/CoScheduler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CoScheduler.dir/main.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoScheduler.dir/main.o -MF CMakeFiles/CoScheduler.dir/main.o.d -o CMakeFiles/CoScheduler.dir/main.o -c /home/gong/projects/CoScheduler/main.cc

CMakeFiles/CoScheduler.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CoScheduler.dir/main.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gong/projects/CoScheduler/main.cc > CMakeFiles/CoScheduler.dir/main.i

CMakeFiles/CoScheduler.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CoScheduler.dir/main.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gong/projects/CoScheduler/main.cc -o CMakeFiles/CoScheduler.dir/main.s

# Object files for target CoScheduler
CoScheduler_OBJECTS = \
"CMakeFiles/CoScheduler.dir/Async.o" \
"CMakeFiles/CoScheduler.dir/BlockWait.o" \
"CMakeFiles/CoScheduler.dir/Coroutine.o" \
"CMakeFiles/CoScheduler.dir/EventScheduler.o" \
"CMakeFiles/CoScheduler.dir/main.o"

# External object files for target CoScheduler
CoScheduler_EXTERNAL_OBJECTS =

CoScheduler: CMakeFiles/CoScheduler.dir/Async.o
CoScheduler: CMakeFiles/CoScheduler.dir/BlockWait.o
CoScheduler: CMakeFiles/CoScheduler.dir/Coroutine.o
CoScheduler: CMakeFiles/CoScheduler.dir/EventScheduler.o
CoScheduler: CMakeFiles/CoScheduler.dir/main.o
CoScheduler: CMakeFiles/CoScheduler.dir/build.make
CoScheduler: CMakeFiles/CoScheduler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gong/projects/CoScheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable CoScheduler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CoScheduler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CoScheduler.dir/build: CoScheduler
.PHONY : CMakeFiles/CoScheduler.dir/build

CMakeFiles/CoScheduler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CoScheduler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CoScheduler.dir/clean

CMakeFiles/CoScheduler.dir/depend:
	cd /home/gong/projects/CoScheduler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gong/projects/CoScheduler /home/gong/projects/CoScheduler /home/gong/projects/CoScheduler/build /home/gong/projects/CoScheduler/build /home/gong/projects/CoScheduler/build/CMakeFiles/CoScheduler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CoScheduler.dir/depend

