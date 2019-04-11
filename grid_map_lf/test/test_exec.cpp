/** @file
 *  Declaration of the test_exec class.
 */

#include <grid_map_lf/LikelihoodField.h>
#include <grid_map_sdf/SignedDistanceField.hpp>
#include <grid_map_core/GridMap.hpp>

int main() {

  grid_map::GridMap grid_map;
  grid_map::SignedDistanceField sdf;
  grid_map::LikelihoodField lf;

  grid_map.setGeometry(grid_map::Length(3, 3), 1.0);
  grid_map::Matrix m;
  m.resize(3, 3);
  m.setZero();
  m << 255, 255, 255,
       255,   1, 255,
       255, 255, 255;
  grid_map.add("occupancy_grid", m);

  sdf.calculateSignedDistanceField(grid_map, "occupancy_grid", 1.0);


  std::cout << grid_map["occupancy_grid"] << std::endl;

  std::cout << sdf << std::endl;

  return 0;
}


