# - Config file for the grid_map_lf package
# It defines the following variables
#  grid_map_lf_INCLUDE_DIRS - include directories for grid_map_lf
#  grid_map_lf_LIBRARIES    - libraries to link against
#  grid_map_lf_EXECUTABLE   - the grid_map_lf executable
include(CMakeFindDependencyMacro)
find_dependency(grid_map_core CONFIG REQUIRED)
find_dependency(grid_map_sdf CONFIG REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/grid_map_lfTargets.cmake")

# ------------------------------------------------------------------------------
# Old CMake & Glorious MTR_Macro support
# ------------------------------------------------------------------------------

# Support Uppercase name
set(GRID_MAP_LF_FOUND TRUE)

# Set find_package variables
get_target_property(grid_map_lf_INCLUDE_DIRS grid_map_lf::grid_map_lf INTERFACE_INCLUDE_DIRECTORIES)
set(grid_map_lf_LIBRARY grid_map_lf)
set(grid_map_lf_LIBRARY_DIR "/usr/lib/")