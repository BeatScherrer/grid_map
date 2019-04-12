# Set cmake version
cmake_minimum_required(VERSION 3.0.2)

# Set project name
project(grid_map)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

add_compile_options(-std=c++11)

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

include(CPack)

#
# Testing
#
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Add subdirectories
add_subdirectory(grid_map_core)
add_subdirectory(grid_map_sdf)
add_subdirectory(grid_map_lf)