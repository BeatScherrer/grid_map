# Set cmake version
cmake_minimum_required(VERSION 3.0.2)

# Set project name
project(grid_map_filters)

#########
# Build #
#########

# Add the library target
add_library(${PROJECT_NAME}
  src/BufferNormalizerFilter.cpp
  src/ColorBlendingFilter.cpp
  src/ColorFillFilter.cpp
  src/ColorMapFilter.cpp
  src/DeletionFilter.cpp
  src/DuplicationFilter.cpp
  src/LightIntensityFilter.cpp
  src/MathExpressionFilter.cpp
  src/MeanInRadiusFilter.cpp
  src/MinInRadiusFilter.cpp
  src/NormalColorMapFilter.cpp
  src/NormalVectorsFilter.cpp
  src/SetBasicLayersFilter.cpp
  src/SlidingWindowMathExpressionFilter.cpp
  src/ThresholdFilter.cpp
  )

# set target include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )

# add an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  grid_map_core
  )

# set target compile options
target_compile_options(${PROJECT_NAME}
  PRIVATE
  $<$<CONFIG:Debug>:-Werror>
  )

###########
# Install #
###########

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION include
)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(
  EXPORT ${PROJECT_NAME}Config
  DESTINATION share/${PROJECT_NAME}/cmake
)

# mark other files for installation
install(
  DIRECTORY doc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# This makes the project importable from the build directory
export(
  TARGETS ${PROJECT_NAME}
  FILE ${PROJECT_NAME}.cmake
)

###########
# Testing #
###########