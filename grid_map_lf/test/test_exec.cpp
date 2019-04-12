/** @file
 *  Declaration of the test_exec class.
 */

#include <grid_map_lf/LikelihoodField.h>
#include <grid_map_sdf/SignedDistanceField.hpp>
#include <grid_map_core/GridMap.hpp>

int main() {

  grid_map::GridMap map({"layer"});
  map.setGeometry(grid_map::Length(1.0, 2.0), 0.1, grid_map::Position());
  map["layer"].setConstant(1.0);
  map.at("layer", grid_map::Index(0, 0)) = -1;

  grid_map::SignedDistanceField sdf;

  sdf.calculateSignedDistanceField(map, "layer", 2.5);

  std::cout << map["layer"] << std::endl;

  std::cout << sdf << std::endl;

  return 0;
}


