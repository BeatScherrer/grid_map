# Set cmake version
cmake_minimum_required(VERSION 3.0.2)


# Add subdirectories
add_subdirectory(grid_map_core)
add_subdirectory(grid_map_sdf)
add_subdirectory(grid_map_lf)

add_subdirectory(submodules)

# Set project name
project(grid_map VERSION 1.0.0)

add_compile_options(-std=c++11 -fPIC)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

#
# Packaging
#
set(CPACK_PACKAGE_NAME "grid_map")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "grid_map package - CPack installation")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Beat Scherrer")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

add_library(grid_map STATIC
  grid_map_core/src/BufferRegion.cpp
  grid_map_core/src/GridMap.cpp
  grid_map_core/src/GridMapMath.cpp
  grid_map_core/src/Polygon.cpp
  grid_map_core/src/SubmapGeometry.cpp
  grid_map_core/src/iterators/CircleIterator.cpp
  grid_map_core/src/iterators/EllipseIterator.cpp
  grid_map_core/src/iterators/GridMapIterator.cpp
  grid_map_core/src/iterators/LineIterator.cpp
  grid_map_core/src/iterators/PolygonIterator.cpp
  grid_map_core/src/iterators/SlidingWindowIterator.cpp
  grid_map_core/src/iterators/SpiralIterator.cpp
  grid_map_core/src/iterators/SubmapIterator.cpp

  grid_map_sdf/src/SignedDistanceField.cpp

  grid_map_lf/src/LikelihoodField.cpp
  )

target_include_directories(grid_map
  PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # <prefix>/include/${PROJECT_NAME}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/grid_map_core/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/grid_map_sdf/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/grid_map_lf/include>
    ${EIGEN3_INCLUDE_DIR}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<CONFIG:Debug>:-Werror>
)

###########
# Install #
###########

include(GNUInstallDirs)

# create export set
install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Targets"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  )

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_LIBDIR})

install(
  DIRECTORY
    grid_map_core/include/
    grid_map_sdf/include/
    grid_map_lf/include/
  DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

# This makes the project importable from the install directory
# Put config file in per-project dir.
install(EXPORT "${PROJECT_NAME}Targets"
  FILE
  "${PROJECT_NAME}Targets.cmake"
  NAMESPACE
  "${PROJECT_NAME}::"
  DESTINATION
  lib/cmake/${PROJECT_NAME})

# install config.cmake files
install(FILES
  "${PROJECT_NAME}Config.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}")

include(CPack)

#
# Testing
#

enable_testing()