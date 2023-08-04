cmake_minimum_required(VERSION 3.5)
project(simple_ros2_serial)

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
find_package(serial REQUIRED)

add_executable(serial src/simple_ros2_serial.cpp)
ament_target_dependencies(serial rclcpp serial)

install(TARGETS
  serial
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
