cmake_minimum_required(VERSION 3.0.2)
project(move_base_benchmark)

find_package(catkin REQUIRED
    COMPONENTS
        actionlib
        base_local_planner
        clear_costmap_recovery
        cmake_modules
        costmap_2d
        dynamic_reconfigure
        geometry_msgs
        message_generation
        move_base_msgs
        nav_core
        nav_msgs
        navfn
        pluginlib
        roscpp
        rospy
        rotate_recovery
        std_srvs
        tf2_geometry_msgs
        tf2_ros
        srpb_logger
        srpb_tooling
)
find_package(Eigen3 REQUIRED)
add_definitions(${EIGEN3_DEFINITIONS})

# FIXME::
# OpenCV dependency is inherited from `srpb_tooling` package however there is some linking issue. Error is:
#
# Errors     << move_base_benchmark:make <WS>/logs/move_base_benchmark/build.make.034.log
# /usr/bin/ld: CMakeFiles/move_base_benchmark_node.dir/src/move_base_node.cpp.o: undefined reference to symbol
# '_ZN2cv6String10deallocateEv'
# /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2: error adding symbols: DSO missing from command line
# collect2: error: ld returned 1 exit status
#
# ${srpb_tooling_LIBRARIES} does not show `opencv` libraries indeed
#
find_package(OpenCV REQUIRED)

# dynamic reconfigure
generate_dynamic_reconfigure_options(
    cfg/MoveBase.cfg
)

catkin_package(
    INCLUDE_DIRS
        include
    LIBRARIES
        move_base_benchmark
    CATKIN_DEPENDS
        dynamic_reconfigure
        geometry_msgs
        move_base_msgs
        nav_msgs
        roscpp
        srpb_logger
        srpb_tooling
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${srpb_logger_INCLUDE_DIRS}
    ${srpb_tooling_INCLUDE_DIRS}
)

# move_base
add_library(move_base_benchmark
  src/move_base.cpp
)
target_link_libraries(move_base_benchmark
    ${Boost_LIBRARIES}
    ${catkin_LIBRARIES}
    ${srpb_logger_LIBRARIES}
    ${srpb_tooling_LIBRARIES}
    # FIXME: see note above
    ${OpenCV_LIBRARIES}
    )
add_dependencies(move_base_benchmark ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(move_base_benchmark_node
  src/move_base_node.cpp
)
add_dependencies(move_base_benchmark_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_base_benchmark_node move_base_benchmark)
set_target_properties(move_base_benchmark_node PROPERTIES OUTPUT_NAME move_base_benchmark)

install(
    TARGETS
        move_base_benchmark_node
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
    TARGETS
        move_base_benchmark
    DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
