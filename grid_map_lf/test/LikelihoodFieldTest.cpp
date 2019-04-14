/** @file
 *
 *  Declaration of the LikelihoodFieldTest class.
 */

#include <grid_map_lf/LikelihoodField.h>
#include <grid_map_core/GridMapMath.hpp>
#include <grid_map_core/iterators/GridMapIterator.hpp>

#include <gtest/gtest.h>

#include <boost/math/distributions/normal.hpp>

#include <iostream>


using namespace grid_map;
using namespace std;

namespace {
double g_sigma = 0.1;
}
 
TEST(LikelihoodField, EmptyMap)
{
  GridMap map({"layer"});
  map.setGeometry(Length(3.0, 3.0), 1.0, Position());
  map["layer"].setConstant(0);

  SignedDistanceField sdf;
  sdf.calculateSignedDistanceField(map, "layer");
  map.add("distance_field", sdf.getData());

  LikelihoodField lf;
  lf.calculateLikelihoodField(map, "distance_field", g_sigma);
  map.add("likelihood_field", lf.getData());

  for (grid_map::GridMapIterator iterator(map); !iterator.isPastEnd(); ++iterator)
  {
    EXPECT_EQ(map.at("likelihood_field", (*iterator)), 0);
  }
}

TEST(LikelihoodField, FullyOccupiedMap)
{
  GridMap map({"layer"});
  map.setGeometry(Length(3.0, 3.0), 1.0, Position());
  map["layer"].setConstant(1);

  SignedDistanceField sdf;
  sdf.calculateSignedDistanceField(map, "layer");
  map.add("distance_field", sdf.getData());

  LikelihoodField lf;
  lf.calculateLikelihoodField(map, "distance_field", g_sigma);
  map.add("likelihood_field", lf.getData());

  for (grid_map::GridMapIterator iterator(map); !iterator.isPastEnd(); ++iterator)
  {
    EXPECT_EQ(map.at("likelihood_field", (*iterator)), 1);
  }
}

TEST(LikelihoodField, MiddlePoint)
{
  GridMap map({"layer"});
  map.setGeometry(Length(3.0, 3.0), 1.0, Position());
  map["layer"].setConstant(0);
  map["layer"](1, 1) = 1; // set middle point to obstacle

  SignedDistanceField sdf;
  sdf.calculateSignedDistanceField(map, "layer");
  map.add("distance_field", sdf.getData());

  LikelihoodField lf;
  lf.calculateLikelihoodField(map, "distance_field", g_sigma);
  map.add("likelihood_field", lf.getData());

  boost::math::normal_distribution<double> normalDistribution(0, g_sigma);
  double normalization = pdf(normalDistribution, 0);

  EXPECT_NEAR(map["layer"](0, 0), pdf(normalDistribution, sqrt(2))/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](0, 1), pdf(normalDistribution, 1)/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](0, 2), pdf(normalDistribution, sqrt(2))/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](1, 0), pdf(normalDistribution, 1)/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](1, 1), pdf(normalDistribution, 0)/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](1, 2), pdf(normalDistribution, 1)/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](2, 0), pdf(normalDistribution, sqrt(2))/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](2, 1), pdf(normalDistribution, 1)/ normalization, 1e-5);
  EXPECT_NEAR(map["layer"](2, 2), pdf(normalDistribution, sqrt(2))/ normalization, 1e-5);
}

TEST(LikelihoodField, getLikelihoodAt)
{
  GridMap map({"layer"});
  map.setGeometry(Length(3.0, 3.0), 1.0, Position());
  map["layer"].setConstant(0);
  map["layer"](1, 1) = 1; // set middle point to obstacle

  SignedDistanceField sdf;
  sdf.calculateSignedDistanceField(map, "layer");
  map.add("distance_field", sdf.getData());

  LikelihoodField lf;
  lf.calculateLikelihoodField(map, "distance_field", g_sigma);
  map.add("likelihood_field", lf.getData());

  boost::math::normal_distribution<double> normalDistribution(0, g_sigma);
  double normalization = pdf(normalDistribution, 0);

  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(0, 0)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(0, 0))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(0, 1)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(0, 1))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(0, 2)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(0, 2))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(1, 0)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(1, 0))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(1, 1)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(1, 1))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(1, 2)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(1, 2))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(2, 0)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(2, 0))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(2, 1)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(2, 1))) / normalization, 1e5);
  EXPECT_NEAR(lf.getLikelihoodAt(grid_map::Position(2, 2)),
          pdf(normalDistribution, sdf.getDistanceAt(grid_map::Position(2, 2))) / normalization, 1e5);
}
