cmake_minimum_required(VERSION 3.0.2)

project(grid_map_lf VERSION 1.6.1)

add_compile_options(-std=c++11)

#########
# Build #
#########
add_library(${PROJECT_NAME}
  src/LikelihoodField.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # <prefix>/include/${PROJECT_NAME}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    grid_map_core::grid_map_core
    grid_map_sdf
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

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir.
install(EXPORT "${PROJECT_NAME}Targets"
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${PROJECT_NAME}::
  DESTINATION
    lib/cmake/${PROJECT_NAME}
)

# install config.cmake files
install(FILES
  ${PROJECT_NAME}Config.cmake DESTINATION lib/cmake/${PROJECT_NAME}
)

add_executable(test_exec
  test/test_exec.cpp
  )

target_link_libraries(test_exec
  grid_map_lf::grid_map_lf
  grid_map_sdf::grid_map_sdf
  grid_map_core::grid_map_core
)
