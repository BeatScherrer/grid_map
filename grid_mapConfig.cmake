# - Config file for the grid_map package
# It defines the following variables
#  grid_map_INCLUDE_DIRS - include directories for grid_map
#  grid_map_LIBRARIES    - libraries to link against
#  grid_map_EXECUTABLE   - the grid_map executable
include(CMakeFindDependencyMacro)


include("${CMAKE_CURRENT_LIST_DIR}/grid_mapTargets.cmake")

# ------------------------------------------------------------------------------
# Old CMake & Glorious MTR_Macro support
# ------------------------------------------------------------------------------

# Set find_package variables
get_target_property(grid_map_INCLUDE_DIRS grid_map::grid_map INTERFACE_INCLUDE_DIRECTORIES)
set(grid_map_LIBRARY grid_map)
set(grid_map_LIBRARY_DIR "/usr/lib/")
