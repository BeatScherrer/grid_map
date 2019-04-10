# Set cmake version
cmake_minimum_required(VERSION 3.0.2)

# Set project name
project(grid_map_sdf VERSION 1.6.1)

add_compile_options(-std=c++11)

# import PCL
find_package(PCL REQUIRED CONFIG COMPONENTS)

#########
# Build #
#########

# Add the library target
add_library(${PROJECT_NAME}
  src/SignedDistanceField.cpp
  )

# set target include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # <prefix>/include/${PROJECT_NAME}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${PCL_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

link_directories(
    ${PCL_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  grid_map_core::grid_map_core
  ${PCL_LIBRARIES}
  )

add_definitions(
    ${PCL_DEFINITIONS}
)

# add an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# set target compile options
target_compile_options(${PROJECT_NAME}
  PRIVATE
  #$<$<CONFIG:Debug>:-Werror>
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

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir.
install(EXPORT "${PROJECT_NAME}Targets"
  FILE
  "${PROJECT_NAME}Targets.cmake"
  NAMESPACE
  "${PROJECT_NAME}::"
  DESTINATION
  lib/cmake/${PROJECT_NAME}
)

# generate config.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION
    "${PROJECT_NAME}_VERSION"
  COMPATIBILITY
    SameMajorVersion
  )

# install config.cmake files
install(FILES
  "${PROJECT_NAME}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}")

###########
# Testing #
###########

#############
# Packaging #
#############