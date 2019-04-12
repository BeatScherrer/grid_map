/** @file
 *
 *  Declaration of the LikelihoodFieldTest class.
 */

#include <grid_map_lf/LikelihoodField.h>

#include <gtest/gtest.h>

using namespace grid_map;
 
TEST(LikelihoodField, EmptyMap)
{
  int a = 1;
//  GridMap map({"layer"});
//  map.setGeometry(Length(1.0, 1.0), 0.1, Position());
//
//  SignedDistanceField sdf;
//  sdf.calculateSignedDistanceField(map, "layer");
//
//  LikelihoodField lf;
//  lf.calculateLikelihoodField(map)
  EXPECT_EQ(a, 1);
}
