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
CMAKE_SOURCE_DIR = /home/pna/Documents/study/pascal_compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pna/Documents/study/pascal_compiler/build

# Include any dependencies generated for this target.
include CMakeFiles/compilier.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compilier.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compilier.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compilier.dir/flags.make

CMakeFiles/compilier.dir/src/inout/classes.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/inout/classes.cpp.o: /home/pna/Documents/study/pascal_compiler/src/inout/classes.cpp
CMakeFiles/compilier.dir/src/inout/classes.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compilier.dir/src/inout/classes.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/inout/classes.cpp.o -MF CMakeFiles/compilier.dir/src/inout/classes.cpp.o.d -o CMakeFiles/compilier.dir/src/inout/classes.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/inout/classes.cpp

CMakeFiles/compilier.dir/src/inout/classes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/inout/classes.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/inout/classes.cpp > CMakeFiles/compilier.dir/src/inout/classes.cpp.i

CMakeFiles/compilier.dir/src/inout/classes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/inout/classes.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/inout/classes.cpp -o CMakeFiles/compilier.dir/src/inout/classes.cpp.s

CMakeFiles/compilier.dir/src/inout/inout.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/inout/inout.cpp.o: /home/pna/Documents/study/pascal_compiler/src/inout/inout.cpp
CMakeFiles/compilier.dir/src/inout/inout.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/compilier.dir/src/inout/inout.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/inout/inout.cpp.o -MF CMakeFiles/compilier.dir/src/inout/inout.cpp.o.d -o CMakeFiles/compilier.dir/src/inout/inout.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/inout/inout.cpp

CMakeFiles/compilier.dir/src/inout/inout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/inout/inout.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/inout/inout.cpp > CMakeFiles/compilier.dir/src/inout/inout.cpp.i

CMakeFiles/compilier.dir/src/inout/inout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/inout/inout.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/inout/inout.cpp -o CMakeFiles/compilier.dir/src/inout/inout.cpp.s

CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o: /home/pna/Documents/study/pascal_compiler/src/exceptions/exceptions.cpp
CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o -MF CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o.d -o CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/exceptions/exceptions.cpp

CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/exceptions/exceptions.cpp > CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.i

CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/exceptions/exceptions.cpp -o CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.s

CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o: /home/pna/Documents/study/pascal_compiler/src/exceptions/error_handler.cpp
CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o -MF CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o.d -o CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/exceptions/error_handler.cpp

CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/exceptions/error_handler.cpp > CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.i

CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/exceptions/error_handler.cpp -o CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.s

CMakeFiles/compilier.dir/src/lexer/classes.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/lexer/classes.cpp.o: /home/pna/Documents/study/pascal_compiler/src/lexer/classes.cpp
CMakeFiles/compilier.dir/src/lexer/classes.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compilier.dir/src/lexer/classes.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/lexer/classes.cpp.o -MF CMakeFiles/compilier.dir/src/lexer/classes.cpp.o.d -o CMakeFiles/compilier.dir/src/lexer/classes.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/lexer/classes.cpp

CMakeFiles/compilier.dir/src/lexer/classes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/lexer/classes.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/lexer/classes.cpp > CMakeFiles/compilier.dir/src/lexer/classes.cpp.i

CMakeFiles/compilier.dir/src/lexer/classes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/lexer/classes.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/lexer/classes.cpp -o CMakeFiles/compilier.dir/src/lexer/classes.cpp.s

CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o: /home/pna/Documents/study/pascal_compiler/src/lexer/lexer.cpp
CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o -MF CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o.d -o CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/lexer/lexer.cpp

CMakeFiles/compilier.dir/src/lexer/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/lexer/lexer.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/lexer/lexer.cpp > CMakeFiles/compilier.dir/src/lexer/lexer.cpp.i

CMakeFiles/compilier.dir/src/lexer/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/lexer/lexer.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/lexer/lexer.cpp -o CMakeFiles/compilier.dir/src/lexer/lexer.cpp.s

CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o: CMakeFiles/compilier.dir/flags.make
CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o: /home/pna/Documents/study/pascal_compiler/src/compilier/compilier.cpp
CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o: CMakeFiles/compilier.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o -MF CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o.d -o CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o -c /home/pna/Documents/study/pascal_compiler/src/compilier/compilier.cpp

CMakeFiles/compilier.dir/src/compilier/compilier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compilier.dir/src/compilier/compilier.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pna/Documents/study/pascal_compiler/src/compilier/compilier.cpp > CMakeFiles/compilier.dir/src/compilier/compilier.cpp.i

CMakeFiles/compilier.dir/src/compilier/compilier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compilier.dir/src/compilier/compilier.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pna/Documents/study/pascal_compiler/src/compilier/compilier.cpp -o CMakeFiles/compilier.dir/src/compilier/compilier.cpp.s

# Object files for target compilier
compilier_OBJECTS = \
"CMakeFiles/compilier.dir/src/inout/classes.cpp.o" \
"CMakeFiles/compilier.dir/src/inout/inout.cpp.o" \
"CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o" \
"CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o" \
"CMakeFiles/compilier.dir/src/lexer/classes.cpp.o" \
"CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o" \
"CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o"

# External object files for target compilier
compilier_EXTERNAL_OBJECTS =

compilier: CMakeFiles/compilier.dir/src/inout/classes.cpp.o
compilier: CMakeFiles/compilier.dir/src/inout/inout.cpp.o
compilier: CMakeFiles/compilier.dir/src/exceptions/exceptions.cpp.o
compilier: CMakeFiles/compilier.dir/src/exceptions/error_handler.cpp.o
compilier: CMakeFiles/compilier.dir/src/lexer/classes.cpp.o
compilier: CMakeFiles/compilier.dir/src/lexer/lexer.cpp.o
compilier: CMakeFiles/compilier.dir/src/compilier/compilier.cpp.o
compilier: CMakeFiles/compilier.dir/build.make
compilier: CMakeFiles/compilier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pna/Documents/study/pascal_compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable compilier"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compilier.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compilier.dir/build: compilier
.PHONY : CMakeFiles/compilier.dir/build

CMakeFiles/compilier.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compilier.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compilier.dir/clean

CMakeFiles/compilier.dir/depend:
	cd /home/pna/Documents/study/pascal_compiler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pna/Documents/study/pascal_compiler /home/pna/Documents/study/pascal_compiler /home/pna/Documents/study/pascal_compiler/build /home/pna/Documents/study/pascal_compiler/build /home/pna/Documents/study/pascal_compiler/build/CMakeFiles/compilier.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compilier.dir/depend

