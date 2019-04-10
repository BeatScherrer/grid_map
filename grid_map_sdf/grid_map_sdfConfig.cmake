# - Config file for the grid_map_core package
# It defines the following variables
#  grid_map_sdf_INCLUDE_DIRS - include directories for grid_map_sdf
#  grid_map_sdf_LIBRARIES    - libraries to link against
#  grid_map_sdf_EXECUTABLE   - the grid_map_sdf executable
include(CMakeFindDependencyMacro)
find_dependency(grid_map_core CONFIG REQUIRED)
find_dependency(PCL CONFIG REQUIRED COMPONENTS)

include("${CMAKE_CURRENT_LIST_DIR}/grid_map_sdfTargets.cmake")

# ------------------------------------------------------------------------------
# Old CMake & Glorious MTR_Macro support
# ------------------------------------------------------------------------------

# Support Uppercase name
set(GRID_MAP_SDF_FOUND TRUE)

# Set find_package variables
get_target_property(grid_map_sdf_INCLUDE_DIRS grid_map_sdf::grid_map_sdf INTERFACE_INCLUDE_DIRECTORIES)
set(grid_map_sdf_LIBRARY grid_map_sdf)
set(grid_map_sdf_LIBRARY_DIR "/usr/lib/")