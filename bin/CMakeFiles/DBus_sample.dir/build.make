# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/belisarius/DBus_sample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/belisarius/DBus_sample/bin

# Include any dependencies generated for this target.
include CMakeFiles/DBus_sample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DBus_sample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DBus_sample.dir/flags.make

CMakeFiles/DBus_sample.dir/main.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DBus_sample.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/main.cpp.o -c /home/belisarius/DBus_sample/main.cpp

CMakeFiles/DBus_sample.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/main.cpp > CMakeFiles/DBus_sample.dir/main.cpp.i

CMakeFiles/DBus_sample.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/main.cpp -o CMakeFiles/DBus_sample.dir/main.cpp.s

CMakeFiles/DBus_sample.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/main.cpp.o.requires

CMakeFiles/DBus_sample.dir/main.cpp.o.provides: CMakeFiles/DBus_sample.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/main.cpp.o.provides

CMakeFiles/DBus_sample.dir/main.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/main.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o: ../src/DBusArgumentFactory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o -c /home/belisarius/DBus_sample/src/DBusArgumentFactory.cpp

CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusArgumentFactory.cpp > CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusArgumentFactory.cpp -o CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o: ../src/DBusContainerArg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o -c /home/belisarius/DBus_sample/src/DBusContainerArg.cpp

CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusContainerArg.cpp > CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusContainerArg.cpp -o CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o: ../src/DBusArgumentPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o -c /home/belisarius/DBus_sample/src/DBusArgumentPack.cpp

CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusArgumentPack.cpp > CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusArgumentPack.cpp -o CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o


CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o: ../src/BusConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o -c /home/belisarius/DBus_sample/src/BusConnection.cpp

CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/BusConnection.cpp > CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.i

CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/BusConnection.cpp -o CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.s

CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o: ../src/DBusServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o -c /home/belisarius/DBus_sample/src/DBusServer.cpp

CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusServer.cpp > CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusServer.cpp -o CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o: ../src/DBusMethodReply.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o -c /home/belisarius/DBus_sample/src/DBusMethodReply.cpp

CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusMethodReply.cpp > CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusMethodReply.cpp -o CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o: ../src/DBusArray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o -c /home/belisarius/DBus_sample/src/DBusArray.cpp

CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusArray.cpp > CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusArray.cpp -o CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o: ../src/DBusInterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o -c /home/belisarius/DBus_sample/src/DBusInterface.cpp

CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusInterface.cpp > CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusInterface.cpp -o CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o: ../src/DBusDictEntry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o -c /home/belisarius/DBus_sample/src/DBusDictEntry.cpp

CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusDictEntry.cpp > CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusDictEntry.cpp -o CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o: ../src/DBusStruct.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o -c /home/belisarius/DBus_sample/src/DBusStruct.cpp

CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusStruct.cpp > CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusStruct.cpp -o CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o: ../src/DBusDictionary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o -c /home/belisarius/DBus_sample/src/DBusDictionary.cpp

CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusDictionary.cpp > CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusDictionary.cpp -o CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o: ../src/DBusArgument.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o -c /home/belisarius/DBus_sample/src/DBusArgument.cpp

CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusArgument.cpp > CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusArgument.cpp -o CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o: ../src/DBusClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o -c /home/belisarius/DBus_sample/src/DBusClient.cpp

CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusClient.cpp > CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusClient.cpp -o CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o: ../src/DBusBasicArgument.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o -c /home/belisarius/DBus_sample/src/DBusBasicArgument.cpp

CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusBasicArgument.cpp > CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusBasicArgument.cpp -o CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o


CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o: CMakeFiles/DBus_sample.dir/flags.make
CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o: ../src/DBusMethod.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o -c /home/belisarius/DBus_sample/src/DBusMethod.cpp

CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/belisarius/DBus_sample/src/DBusMethod.cpp > CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.i

CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/belisarius/DBus_sample/src/DBusMethod.cpp -o CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.s

CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.requires:

.PHONY : CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.requires

CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.provides: CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.requires
	$(MAKE) -f CMakeFiles/DBus_sample.dir/build.make CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.provides.build
.PHONY : CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.provides

CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.provides.build: CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o


# Object files for target DBus_sample
DBus_sample_OBJECTS = \
"CMakeFiles/DBus_sample.dir/main.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o" \
"CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o"

# External object files for target DBus_sample
DBus_sample_EXTERNAL_OBJECTS =

DBus_sample: CMakeFiles/DBus_sample.dir/main.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o
DBus_sample: CMakeFiles/DBus_sample.dir/build.make
DBus_sample: /usr/lib/x86_64-linux-gnu/libdbus-1.so
DBus_sample: CMakeFiles/DBus_sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/belisarius/DBus_sample/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX executable DBus_sample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DBus_sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DBus_sample.dir/build: DBus_sample

.PHONY : CMakeFiles/DBus_sample.dir/build

CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/main.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusArgumentFactory.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusContainerArg.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusArgumentPack.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/BusConnection.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusServer.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusMethodReply.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusArray.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusInterface.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusDictEntry.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusStruct.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusDictionary.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusArgument.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusClient.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusBasicArgument.cpp.o.requires
CMakeFiles/DBus_sample.dir/requires: CMakeFiles/DBus_sample.dir/src/DBusMethod.cpp.o.requires

.PHONY : CMakeFiles/DBus_sample.dir/requires

CMakeFiles/DBus_sample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DBus_sample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DBus_sample.dir/clean

CMakeFiles/DBus_sample.dir/depend:
	cd /home/belisarius/DBus_sample/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/belisarius/DBus_sample /home/belisarius/DBus_sample /home/belisarius/DBus_sample/bin /home/belisarius/DBus_sample/bin /home/belisarius/DBus_sample/bin/CMakeFiles/DBus_sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DBus_sample.dir/depend

