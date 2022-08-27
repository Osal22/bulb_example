cmake_minimum_required(VERSION 3.0.2)
project(bulb)


add_compile_options(-std=c++2a)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(catkin REQUIRED COMPONENTS nodelet)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
find_package(Boost REQUIRED COMPONENTS thread)



# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )




catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bulb
#  CATKIN_DEPENDS roscpp rospy
#  DEPENDS system_lib
)

#
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
add_executable(${PROJECT_NAME}  "src/main.cpp"
                                "src/ros_topic.cpp"
                                "qml.qrc"
                              )
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets ${catkin_LIBRARIES})


