# Set cmake version
cmake_minimum_required(VERSION 3.0.2)

# Set project name
project(grid_map_cv)

# import openCV
find_package(OpenCV REQUIRED CONFIG)

#########
# Build #
#########

# Add the library target
add_library(${PROJECT_NAME}
  src/GridMapCvProcessing.cpp
  )

# set target include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${}
)

# add an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    grid_map_core
    OpenCV
  )

# set target compile options
target_compile_options(${PROJECT_NAME}
  PRIVATE
  $<$<CONFIG:Debug>:-Werror>
  )

###########
# Install #
###########

