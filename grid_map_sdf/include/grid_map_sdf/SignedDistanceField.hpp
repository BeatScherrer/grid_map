/*
 * SignedDistanceField.hpp
 *
 *  Created on: Aug 16, 2017
 *     Authors: Takahiro Miki, Peter Fankhauser
 *   Institute: ETH Zurich, ANYbotics
 */

#pragma once

#include <grid_map_core/GridMap.hpp>

// PCL
#include <pcl/point_types.h>
#include <pcl/conversions.h>

// STL
#include <string>
#include <vector>
#include <iostream>

namespace grid_map {

/** Class to calculate the signed distance field for given obstacles.
 *
 */
class SignedDistanceField
{
 public:
  /// Default constructor
  SignedDistanceField();

  /// Default destructor.
  virtual ~SignedDistanceField();

  /** Calculates the signed distance field for a given occupancy grid.
   *
   * @param gridMap Grid map for which a distance field is to be constructed.
   * @param layer Layer of the grid map for which a distance field is to be constructed.
   * @param heightClearance ?
   */
  void calculateSignedDistanceField(const GridMap& gridMap, const std::string& layer, const double heightClearance);

  /** Retrieves the distance to the nearest obstacle at the given @param position.
   *
   * @param position Position for which the distance is returned.
   * @return Distance to nearest obstacle at position.
   */
  double getDistanceAt(const Position3& position) const;

  /** Retrieves the three dimensional distance gradient at a given position.
   *
   * @param position Position of which the gradient is calculated.
   * @return Vector with the three dimensional gradient at the given position.
   */
  Vector3 getDistanceGradientAt(const Position3& position) const;

  /** Interpolates the distance of a given position from the adjacent cell entries.
   *
   * @param position Position for which the distance is returned.
   * @return Interpolated distance to the nearest obstacle.
   */
  double getInterpolatedDistanceAt(const Position3& position) const;

  /** Converts the distance field to a point cloud.
   *
   * @param[out] points Point cloud of the distance field.
   */
  void convertToPointCloud(pcl::PointCloud<pcl::PointXYZI>& points) const;

  /** Output stream operator.
   *  Proxies to the matrix.
   *
   * @param out Output stream.
   * @param in Distance field
   * @return ostream object to allow chaining.
   */
  friend std::ostream& operator << (std::ostream &out, const SignedDistanceField& in);

 private:
  /** Retrieves the two dimensional signed distance field.
   *
   * @param data Data for which the distance field is calculated.
   * @return Matrix of the calculated signed distance field.
   */
  Matrix getPlanarSignedDistanceField(Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& data) const;

  /// Cell resolution [m/pix].
  double resolution_;

  /// Size of the Matrix holding the data.
  Size size_;

  /// Position of the map.
  Position position_;

  /// Vector of Matrices holding three dimensional distance data.
  std::vector<Matrix> data_;

  /// Z start height index.
  float zIndexStartHeight_;

  /// Maximum distance in the distance field.
  float maxDistance_;

  /// Lowest height.
  const float lowestHeight_;
};

} /* namespace */
