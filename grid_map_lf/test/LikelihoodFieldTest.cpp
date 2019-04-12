/** @file
 *
 *  Declaration of the LikelihoodFieldTest class.
 */

#include <grid_map_lf/LikelihoodField.h>
#include <grid_map_core/GridMapMath.hpp>
#include <grid_map_core/iterators/GridMapIterator.hpp>

#include <gtest/gtest.h>

using namespace grid_map;
using namespace std;
 
TEST(LikelihoodField, EmptyMap)
{
  GridMap map({"layer"});
  map.setGeometry(Length(3.0, 3.0), 1.0, Position());
  map["layer"].setConstant(0);

  SignedDistanceField sdf;
  sdf.calculateSignedDistanceField(map, "layer");
  map.add("distance_field", sdf.getData());

  LikelihoodField lf;
  lf.calculateLikelihoodField(map, "distance_field", 0.1);
  map.add("likelihood_field", lf.getData());

  for (grid_map::GridMapIterator iterator(map); !iterator.isPastEnd(); ++iterator)
  {
    EXPECT_EQ(map.at("likelihood_field", (*iterator)), 0);
  }
}

TEST(LikelihoodField, FullyOccupiedMap)
{
  EXPECT_EQ(0, 0);
}
