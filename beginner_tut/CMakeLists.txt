cmake_minimum_required(VERSION 2.8.3)
project(beginner_tut)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation)

catkin_python_setup()

add_message_files(
  FILES
  Num.msg
)

add_service_files(
  FILES
  AddTwoInts.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES beginner_tut
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
   CATKIN_DEPENDS roscpp message_runtime
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tut_gencpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tut_gencpp)

install(PROGRAMS
  scripts/add_two_ints_client.py
  scripts/add_two_ints_server.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
