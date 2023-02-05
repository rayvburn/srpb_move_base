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
        people_msgs
        people_msgs_utils
        pluginlib
        roscpp
        rospy
        rotate_recovery
        std_srvs
        tf2_geometry_msgs
        tf2_ros
)
find_package(Eigen3 REQUIRED)
add_definitions(${EIGEN3_DEFINITIONS})

# Benchmark
find_package(Ceres REQUIRED)
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
        people_msgs
        people_msgs_utils
        roscpp
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${CERES_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${people_msgs_utils_INCLUDE_DIRS}
)

# move_base
add_library(move_base_benchmark
  src/move_base.cpp
  src/obs_dist_calculator.cpp
  src/people_logger.cpp
)
target_link_libraries(move_base_benchmark
    ${Boost_LIBRARIES}
    ${catkin_LIBRARIES}
    ${CERES_LIBRARIES}
    ${OpenCV_LIBS}
    ${people_msgs_utils_LIBRARIES}
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

## Testing
# catkin run_tests --no-deps move_base_benchmark --verbose
if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(test_people_logger test/test_people_logger.cpp)
  if(TARGET test_people_logger)
    target_link_libraries(test_people_logger move_base_benchmark)
  endif()
endif()
