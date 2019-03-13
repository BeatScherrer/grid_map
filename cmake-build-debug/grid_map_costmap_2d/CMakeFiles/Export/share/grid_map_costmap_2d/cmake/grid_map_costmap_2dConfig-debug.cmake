#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "grid_map_costmap_2d" for configuration "Debug"
set_property(TARGET grid_map_costmap_2d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(grid_map_costmap_2d PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libgrid_map_costmap_2d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS grid_map_costmap_2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_grid_map_costmap_2d "${_IMPORT_PREFIX}/lib/libgrid_map_costmap_2d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
