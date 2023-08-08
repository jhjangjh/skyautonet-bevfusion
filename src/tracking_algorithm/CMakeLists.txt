cmake_minimum_required(VERSION 3.5)
project(tracking_algorithm)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(custom_msgs REQUIRED)


include_directories(include)

add_executable(sort_ros src/main.cpp src/Hungarian.cpp src/Sort.cpp src/SortRect.cpp src/SortRos.cpp src/Tracker.cpp src/TrackerState.cpp)
ament_target_dependencies(sort_ros
rclcpp
std_msgs
visualization_msgs
OpenCV
custom_msgs
)

install(TARGETS
  sort_ros
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

# add_executable(sort_ros_custom src/main.cpp src/Hungarian.cpp src/Sort.cpp src/SortRect.cpp src/SortRos_custom.cpp src/Tracker.cpp src/TrackerState.cpp)
# ament_target_dependencies(sort_ros_custom
# rclcpp
# std_msgs
# visualization_msgs
# OpenCV
# custom_msgs
# )

# install(TARGETS
#   sort_ros_custom
#   DESTINATION lib/${PROJECT_NAME}
# )


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
