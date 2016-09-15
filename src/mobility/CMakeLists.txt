cmake_minimum_required(VERSION 2.8.3)
project(mobility)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  random_numbers
  message_generation
  shared_messages
)

catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs std_msgs random_numbers message_runtime shared_messages
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(
  mobility 
  src/mobility.cpp
  src/ALSAController.cpp
  src/TargetDetectionEvent.cpp
  src/Coordinate.cpp
)

add_dependencies(mobility ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  mobility
  ${catkin_LIBRARIES}
)

