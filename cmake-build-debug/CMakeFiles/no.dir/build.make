# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/wangyongchun/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6397.106/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/wangyongchun/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6397.106/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangyongchun/www/study/c/unix-advanced-programing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/no.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/no.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/no.dir/flags.make

CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o: CMakeFiles/no.dir/flags.make
CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o: ../first-chapter/first_chapter_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o   -c /Users/wangyongchun/www/study/c/unix-advanced-programing/first-chapter/first_chapter_test.c

CMakeFiles/no.dir/first-chapter/first_chapter_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/no.dir/first-chapter/first_chapter_test.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/wangyongchun/www/study/c/unix-advanced-programing/first-chapter/first_chapter_test.c > CMakeFiles/no.dir/first-chapter/first_chapter_test.c.i

CMakeFiles/no.dir/first-chapter/first_chapter_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/no.dir/first-chapter/first_chapter_test.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/wangyongchun/www/study/c/unix-advanced-programing/first-chapter/first_chapter_test.c -o CMakeFiles/no.dir/first-chapter/first_chapter_test.c.s

# Object files for target no
no_OBJECTS = \
"CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o"

# External object files for target no
no_EXTERNAL_OBJECTS =

no: CMakeFiles/no.dir/first-chapter/first_chapter_test.c.o
no: CMakeFiles/no.dir/build.make
no: CMakeFiles/no.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable no"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/no.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/no.dir/build: no

.PHONY : CMakeFiles/no.dir/build

CMakeFiles/no.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/no.dir/cmake_clean.cmake
.PHONY : CMakeFiles/no.dir/clean

CMakeFiles/no.dir/depend:
	cd /Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangyongchun/www/study/c/unix-advanced-programing /Users/wangyongchun/www/study/c/unix-advanced-programing /Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug /Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug /Users/wangyongchun/www/study/c/unix-advanced-programing/cmake-build-debug/CMakeFiles/no.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/no.dir/depend

