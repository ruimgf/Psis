# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/rui/code/psis_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rui/code/psis_project

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rui/code/psis_project/CMakeFiles /home/rui/code/psis_project/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rui/code/psis_project/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named client

# Build rule for target.
client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client
.PHONY : client

# fast build rule for target.
client/fast:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/build
.PHONY : client/fast

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/build
.PHONY : server/fast

#=============================================================================
# Target rules for targets named client-exe-1

# Build rule for target.
client-exe-1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client-exe-1
.PHONY : client-exe-1

# fast build rule for target.
client-exe-1/fast:
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/build
.PHONY : client-exe-1/fast

#=============================================================================
# Target rules for targets named cli-exe-par-1

# Build rule for target.
cli-exe-par-1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cli-exe-par-1
.PHONY : cli-exe-par-1

# fast build rule for target.
cli-exe-par-1/fast:
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/build
.PHONY : cli-exe-par-1/fast

cli-exe-1.o: cli-exe-1.c.o

.PHONY : cli-exe-1.o

# target to build an object file
cli-exe-1.c.o:
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/cli-exe-1.c.o
.PHONY : cli-exe-1.c.o

cli-exe-1.i: cli-exe-1.c.i

.PHONY : cli-exe-1.i

# target to preprocess a source file
cli-exe-1.c.i:
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/cli-exe-1.c.i
.PHONY : cli-exe-1.c.i

cli-exe-1.s: cli-exe-1.c.s

.PHONY : cli-exe-1.s

# target to generate assembly for a file
cli-exe-1.c.s:
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/cli-exe-1.c.s
.PHONY : cli-exe-1.c.s

cli-exe-par-1.o: cli-exe-par-1.c.o

.PHONY : cli-exe-par-1.o

# target to build an object file
cli-exe-par-1.c.o:
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/cli-exe-par-1.c.o
.PHONY : cli-exe-par-1.c.o

cli-exe-par-1.i: cli-exe-par-1.c.i

.PHONY : cli-exe-par-1.i

# target to preprocess a source file
cli-exe-par-1.c.i:
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/cli-exe-par-1.c.i
.PHONY : cli-exe-par-1.c.i

cli-exe-par-1.s: cli-exe-par-1.c.s

.PHONY : cli-exe-par-1.s

# target to generate assembly for a file
cli-exe-par-1.c.s:
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/cli-exe-par-1.c.s
.PHONY : cli-exe-par-1.c.s

client.o: client.c.o

.PHONY : client.o

# target to build an object file
client.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.o
.PHONY : client.c.o

client.i: client.c.i

.PHONY : client.i

# target to preprocess a source file
client.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.i
.PHONY : client.c.i

client.s: client.c.s

.PHONY : client.s

# target to generate assembly for a file
client.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.c.s
.PHONY : client.c.s

list.o: list.c.o

.PHONY : list.o

# target to build an object file
list.c.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/list.c.o
.PHONY : list.c.o

list.i: list.c.i

.PHONY : list.i

# target to preprocess a source file
list.c.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/list.c.i
.PHONY : list.c.i

list.s: list.c.s

.PHONY : list.s

# target to generate assembly for a file
list.c.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/list.c.s
.PHONY : list.c.s

psiskv.o: psiskv.c.o

.PHONY : psiskv.o

# target to build an object file
psiskv.c.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/psiskv.c.o
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/psiskv.c.o
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/psiskv.c.o
.PHONY : psiskv.c.o

psiskv.i: psiskv.c.i

.PHONY : psiskv.i

# target to preprocess a source file
psiskv.c.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/psiskv.c.i
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/psiskv.c.i
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/psiskv.c.i
.PHONY : psiskv.c.i

psiskv.s: psiskv.c.s

.PHONY : psiskv.s

# target to generate assembly for a file
psiskv.c.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/psiskv.c.s
	$(MAKE) -f CMakeFiles/client-exe-1.dir/build.make CMakeFiles/client-exe-1.dir/psiskv.c.s
	$(MAKE) -f CMakeFiles/cli-exe-par-1.dir/build.make CMakeFiles/cli-exe-par-1.dir/psiskv.c.s
.PHONY : psiskv.c.s

server.o: server.c.o

.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i

.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s

.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.s
.PHONY : server.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... client"
	@echo "... server"
	@echo "... client-exe-1"
	@echo "... cli-exe-par-1"
	@echo "... cli-exe-1.o"
	@echo "... cli-exe-1.i"
	@echo "... cli-exe-1.s"
	@echo "... cli-exe-par-1.o"
	@echo "... cli-exe-par-1.i"
	@echo "... cli-exe-par-1.s"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... list.o"
	@echo "... list.i"
	@echo "... list.s"
	@echo "... psiskv.o"
	@echo "... psiskv.i"
	@echo "... psiskv.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

