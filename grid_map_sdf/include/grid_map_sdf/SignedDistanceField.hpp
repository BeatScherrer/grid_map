/*
 * SignedDistanceField.hpp
 *
 *  Created on: Aug 16, 2017
 *     Authors: Takahiro Miki, Peter Fankhauser
 *   Institute: ETH Zurich, ANYbotics
 */

#pragma once

#include <grid_map_core/GridMap.hpp>

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
  virtual ~SignedDistanceField() = default;

  const Size& getSize() const;

  /** Calculates the signed distance field for a given occupancy grid.
   *
   * @param gridMap Grid map for which a distance field is to be constructed.
   * @param layer Layer of the grid map for which a distance field is to be constructed.
   * @param heightClearance ?
   */
  void calculateSignedDistanceField(const GridMap& gridMap, const std::string& layer, const int occupiedValue = 1);

  /** Retrieves the distance to the nearest obstacle at the given @param position.
   *
   * @param position Position for which the distance is returned.
   * @return Distance to nearest obstacle at position.
   */
  double getDistanceAt(const Vector& position) const;

  /** Interpolates the distance of a given position from the adjacent cell entries.
   *
   * @param position Position for which the distance is returned.
   * @return Interpolated distance to the nearest obstacle.
   */
  double getInterpolatedDistanceAt(const Vector& position) const;

  /** Output stream operator.
   *  Proxies to the matrix.
   *
   * @param out Output stream.
   * @param in Distance field
   * @return ostream object to allow chaining.
   */
  friend std::ostream& operator << (std::ostream &out, const SignedDistanceField& in);

 private:
  /** Retrieves the two dimensional planar signed distance field.
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
  Matrix data_;

  /// Maximum distance in the distance field.
  float maxDistance_;

};

} /* namespace */
