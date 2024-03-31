cmake_minimum_required(VERSION 3.8)
project(sensor_communication)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(bupt_can REQUIRED)
find_package(bupt_interfaces REQUIRED)

aux_source_directory (src SRC_LIST)
include_directories (include/sensor_communication)

add_executable(senser_publisher ${SRC_LIST} ~/bupt_code/bupt_can_node/src/bupt_can.cpp)

ament_target_dependencies(senser_publisher 
  rclcpp
  bupt_can 
  bupt_interfaces
)

install(TARGETS
  senser_publisher
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
