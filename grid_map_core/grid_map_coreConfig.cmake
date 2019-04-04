# - Config file for the grid_map_core package
# It defines the following variables
#  grid_map_core_INCLUDE_DIRS - include directories for grid_map_core
#  grid_map_core_LIBRARIES    - libraries to link against
#  grid_map_core_EXECUTABLE   - the grid_map_core executable

include("${CMAKE_CURRENT_LIST_DIR}/grid_map_coreTargets.cmake")

# ------------------------------------------------------------------------------
# Old CMake & Glorious MTR_Macro support
# ------------------------------------------------------------------------------

# Support Uppercase name
set(GRID_MAP_CORE_FOUND TRUE)

# Set find_package variables
get_target_property(grid_map_core_INCLUDE_DIRS grid_map_core::grid_map_core INTERFACE_INCLUDE_DIRECTORIES)
set(grid_map_core_LIBRARY grid_map_core)
set(grid_map_core_LIBRARY_DIR "/usr/lib/")