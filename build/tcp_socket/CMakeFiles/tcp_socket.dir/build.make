# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/bev/bev_ws/src/tcp_socket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bev/bev_ws/build/tcp_socket

# Include any dependencies generated for this target.
include CMakeFiles/tcp_socket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_socket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_socket.dir/flags.make

CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o: CMakeFiles/tcp_socket.dir/flags.make
CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o: /home/bev/bev_ws/src/tcp_socket/src/tcp_socket_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bev/bev_ws/build/tcp_socket/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o -c /home/bev/bev_ws/src/tcp_socket/src/tcp_socket_server.cpp

CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bev/bev_ws/src/tcp_socket/src/tcp_socket_server.cpp > CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.i

CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bev/bev_ws/src/tcp_socket/src/tcp_socket_server.cpp -o CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.s

# Object files for target tcp_socket
tcp_socket_OBJECTS = \
"CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o"

# External object files for target tcp_socket
tcp_socket_EXTERNAL_OBJECTS =

tcp_socket: CMakeFiles/tcp_socket.dir/src/tcp_socket_server.cpp.o
tcp_socket: CMakeFiles/tcp_socket.dir/build.make
tcp_socket: /opt/ros/foxy/lib/librclcpp.so
tcp_socket: /home/bev/bev_ws/install/custom_msgs/lib/libcustom_msgs__rosidl_typesupport_introspection_c.so
tcp_socket: /home/bev/bev_ws/install/custom_msgs/lib/libcustom_msgs__rosidl_typesupport_c.so
tcp_socket: /home/bev/bev_ws/install/custom_msgs/lib/libcustom_msgs__rosidl_typesupport_introspection_cpp.so
tcp_socket: /home/bev/bev_ws/install/custom_msgs/lib/libcustom_msgs__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/librcl.so
tcp_socket: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/librcl_interfaces__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/librmw_implementation.so
tcp_socket: /opt/ros/foxy/lib/librmw.so
tcp_socket: /opt/ros/foxy/lib/librcl_logging_spdlog.so
tcp_socket: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
tcp_socket: /opt/ros/foxy/lib/librcl_yaml_param_parser.so
tcp_socket: /opt/ros/foxy/lib/libyaml.so
tcp_socket: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/libtracetools.so
tcp_socket: /home/bev/bev_ws/install/custom_msgs/lib/libcustom_msgs__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/libstd_msgs__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_generator_c.so
tcp_socket: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/librosidl_typesupport_introspection_cpp.so
tcp_socket: /opt/ros/foxy/lib/librosidl_typesupport_introspection_c.so
tcp_socket: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/librosidl_typesupport_cpp.so
tcp_socket: /opt/ros/foxy/lib/librosidl_typesupport_c.so
tcp_socket: /opt/ros/foxy/lib/librcpputils.so
tcp_socket: /opt/ros/foxy/lib/librosidl_runtime_c.so
tcp_socket: /opt/ros/foxy/lib/librcutils.so
tcp_socket: CMakeFiles/tcp_socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bev/bev_ws/build/tcp_socket/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tcp_socket"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_socket.dir/build: tcp_socket

.PHONY : CMakeFiles/tcp_socket.dir/build

CMakeFiles/tcp_socket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_socket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_socket.dir/clean

CMakeFiles/tcp_socket.dir/depend:
	cd /home/bev/bev_ws/build/tcp_socket && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bev/bev_ws/src/tcp_socket /home/bev/bev_ws/src/tcp_socket /home/bev/bev_ws/build/tcp_socket /home/bev/bev_ws/build/tcp_socket /home/bev/bev_ws/build/tcp_socket/CMakeFiles/tcp_socket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_socket.dir/depend

