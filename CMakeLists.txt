cmake_minimum_required(VERSION 3.16.3...3.20)
project(haptic_feedback_generation)

add_definitions(-std=c++17)
add_compile_options(-Wall)
add_compile_options(-Wno-deprecated)
add_compile_options(-g)


##############################################################################
# Find dependencies
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(joy REQUIRED)
find_package(tf2 REQUIRED)
find_package(kacanopen REQUIRED)
find_package(brunner_can_interface REQUIRED)
find_package(haptic_station_interface REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(hammer_msgs REQUIRED)
find_package(haptic_station_msgs REQUIRED)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS date_time system thread)
find_package(PCL REQUIRED QUIET)
find_package(VTK REQUIRED)

# Eigen 3.2 (Wily) only provides EIGEN3_INCLUDE_DIR, not EIGEN3_INCLUDE_DIRS
if(NOT EIGEN3_INCLUDE_DIRS)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()


##############################################################################
# Define package
##############################################################################

ament_export_dependencies(
    rclcpp
    rclpy
    joy
    tf2
    brunner_can_interface
    haptic_station_interface
    kacanopen
    std_msgs
    sensor_msgs
    hammer_msgs
    haptic_station_msgs
)

###########
## Build ##
###########

## Declare a cpp library
add_library(haptic_feedback_generation_lib
  src/hapticFeedbackGenerator.cpp
)

target_include_directories(haptic_feedback_generation_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(haptic_feedback_generation_lib
    rclcpp
    rclpy
    joy
    tf2
    # brunner_can_interface
    # haptic_station_interface
    kacanopen
    std_msgs
    sensor_msgs
    hammer_msgs
    haptic_station_msgs
)

target_link_libraries(haptic_feedback_generation_lib
  brunner_can_interface::brunner_can_interface_lib
  haptic_station_interface::haptic_station_interface_lib
)

## MAIN NODES

add_executable(FeedbackGenerator
  src/haptic_feedback_generator_node.cpp
)
ament_target_dependencies(FeedbackGenerator
  rclcpp
  rclpy
  joy
  tf2
  # brunner_can_interface
  kacanopen
  std_msgs
  sensor_msgs
  hammer_msgs
  haptic_station_msgs
)
target_link_libraries(FeedbackGenerator
haptic_feedback_generation_lib
)
target_link_libraries(haptic_feedback_generation_lib
  brunner_can_interface::brunner_can_interface_lib
  haptic_station_interface::haptic_station_interface_lib
)

#############
## Install ##
#############

install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY include/ 
  DESTINATION include
)

install(
  TARGETS
    haptic_feedback_generation_lib
    FeedbackGenerator
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  INCLUDES DESTINATION include
)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_package()
