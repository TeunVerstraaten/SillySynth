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
CMAKE_SOURCE_DIR = /home/pc/Documents/Code/C++/PortAudio/portaudio/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pc/Documents/Code/C++/PortAudio/portaudio/examples

# Include any dependencies generated for this target.
include CMakeFiles/paex_record.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/paex_record.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/paex_record.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/paex_record.dir/flags.make

CMakeFiles/paex_record.dir/paex_record.o: CMakeFiles/paex_record.dir/flags.make
CMakeFiles/paex_record.dir/paex_record.o: paex_record.c
CMakeFiles/paex_record.dir/paex_record.o: CMakeFiles/paex_record.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pc/Documents/Code/C++/PortAudio/portaudio/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/paex_record.dir/paex_record.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/paex_record.dir/paex_record.o -MF CMakeFiles/paex_record.dir/paex_record.o.d -o CMakeFiles/paex_record.dir/paex_record.o -c /home/pc/Documents/Code/C++/PortAudio/portaudio/examples/paex_record.c

CMakeFiles/paex_record.dir/paex_record.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/paex_record.dir/paex_record.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pc/Documents/Code/C++/PortAudio/portaudio/examples/paex_record.c > CMakeFiles/paex_record.dir/paex_record.i

CMakeFiles/paex_record.dir/paex_record.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/paex_record.dir/paex_record.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pc/Documents/Code/C++/PortAudio/portaudio/examples/paex_record.c -o CMakeFiles/paex_record.dir/paex_record.s

# Object files for target paex_record
paex_record_OBJECTS = \
"CMakeFiles/paex_record.dir/paex_record.o"

# External object files for target paex_record
paex_record_EXTERNAL_OBJECTS =

paex_record: CMakeFiles/paex_record.dir/paex_record.o
paex_record: CMakeFiles/paex_record.dir/build.make
paex_record: CMakeFiles/paex_record.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pc/Documents/Code/C++/PortAudio/portaudio/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable paex_record"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/paex_record.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/paex_record.dir/build: paex_record
.PHONY : CMakeFiles/paex_record.dir/build

CMakeFiles/paex_record.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/paex_record.dir/cmake_clean.cmake
.PHONY : CMakeFiles/paex_record.dir/clean

CMakeFiles/paex_record.dir/depend:
	cd /home/pc/Documents/Code/C++/PortAudio/portaudio/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pc/Documents/Code/C++/PortAudio/portaudio/examples /home/pc/Documents/Code/C++/PortAudio/portaudio/examples /home/pc/Documents/Code/C++/PortAudio/portaudio/examples /home/pc/Documents/Code/C++/PortAudio/portaudio/examples /home/pc/Documents/Code/C++/PortAudio/portaudio/examples/CMakeFiles/paex_record.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/paex_record.dir/depend

