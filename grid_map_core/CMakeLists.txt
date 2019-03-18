# Set cmake version
cmake_minimum_required(VERSION 3.0.2)

# Set project name
project(grid_map_core VERSION 1.0.0)

add_compile_options(-std=c++11)

# import Eigen3
find_package(Eigen3 3.2.2 REQUIRED)

## Define Eigen addons.
include(cmake/${PROJECT_NAME}-extras.cmake)

#########
# Build #
#########

# Add the library target
add_library(${PROJECT_NAME}
  src/BufferRegion.cpp
  src/GridMap.cpp
  src/GridMapMath.cpp
  src/Polygon.cpp
  src/SubmapGeometry.cpp
  src/iterators/CircleIterator.cpp
  src/iterators/EllipseIterator.cpp
  src/iterators/GridMapIterator.cpp
  src/iterators/LineIterator.cpp
  src/iterators/PolygonIterator.cpp
  src/iterators/SlidingWindowIterator.cpp
  src/iterators/SubmapIterator.cpp
)

# set target include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # <prefix>/include/${PROJECT_NAME}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${EIGEN3_INCLUDE_DIR}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# add an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# set target compile options
target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<CONFIG:Debug>:-Werror>
)

###########
# Install #
###########

include(GNUInstallDirs)

# 'make install' to the right locations
install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Targets"
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir.
install(EXPORT "${PROJECT_NAME}Targets"
  FILE "${PROJECT_NAME}Targets.cmake"
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION lib/cmake/${PROJECT_NAME})

# generate config.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${PROJECT_NAME}_VERSION"
  COMPATIBILITY SameMajorVersion
  )

# install config.cmake files
install(FILES "${PROJECT_NAME}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}")

###########
# Testing #
###########

#############
# Packaging #
#############

message(STATUS ${PROJECT_VERSION})

set(CPACK_PACKAGE_NAME "grid_map")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "grid_map package - CPack installation")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Beat Scherrer")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

include(CPack)