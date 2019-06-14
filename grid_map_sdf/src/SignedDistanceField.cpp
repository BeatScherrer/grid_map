/*
 * SignedDistanceField.hpp
 *
 *  Created on: Aug 16, 2017
 *     Authors: Takahiro Miki, Peter Fankhauser
 *   Institute: ETH Zurich, ANYbotics
 */

#include "grid_map_sdf/SignedDistanceField.hpp"
#include "grid_map_sdf/distance_transform/dt.h"

#include <grid_map_core/GridMap.hpp>
#include <limits>
#include <cmath>

using namespace distance_transform;

namespace grid_map {

SignedDistanceField::SignedDistanceField()
    : maxDistance_(std::numeric_limits<float>::max()),
      resolution_(0.0)
{
}

// -----------------------------------------------------------------------------
// Getters
// -----------------------------------------------------------------------------

const Size& SignedDistanceField::getSize() const
{
  return size_;
}

const Matrix& SignedDistanceField::getData() const
{
  return data_;
}

void SignedDistanceField::calculateSignedDistanceField(const GridMap& gridMap, const std::string& layer, const int occupiedValue)
{
  data_.setZero();
  resolution_ = gridMap.getResolution();
  position_ = gridMap.getPosition();
  size_ = gridMap.getSize();

  Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> occupancyGrid;
  occupancyGrid.resize(size_(0), size_(1));

  // store unknown indices
  std::vector<grid_map::Index> nan_indices;

  // set cells with values = occupied values to 1 others to 0
  for (int i = 0; i < size_(0); ++i)
  {
    for(int j = 0; j < size_(1); ++j)
    {
      if(isnan(gridMap[layer](i, j)))
      {
        std::cout << "is NaN" << std::endl;
        nan_indices.emplace_back(i, j);
      }
      else
      {
        occupancyGrid(i, j) = gridMap[layer](i, j) == occupiedValue;
      }
    }
  }

  // Transform the occupancy grid
  data_ = getPlanarSignedDistanceField(occupancyGrid);

  // propagate nans (unknown space)
  for(const auto& i : nan_indices)
  {
    data_(i[0], i[1]) = NAN;
  }
}

double SignedDistanceField::getDistanceAt(const Vector& position) const
{
  double xCenter = size_.x() / 2.0;
  double yCenter = size_.y() / 2.0;
  int i = std::round(xCenter - (position.x() - position_.x()) / resolution_);
  int j = std::round(yCenter - (position.y() - position_.y()) / resolution_);
  i = std::max(i, 0);
  i = std::min(i, size_.x() - 1);
  j = std::max(j, 0);
  j = std::min(j, size_.y() - 1);

  return data_(i, j);
}

std::ostream& operator << (std::ostream &out, const SignedDistanceField& in)
{
  out << in.data_ << std::endl;
  return out;
}

// -----------------------------------------------------------------------------
// Private
// -----------------------------------------------------------------------------

grid_map::Matrix SignedDistanceField::getPlanarSignedDistanceField(Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic>& data) const
{
  image<uchar>* input = new image<uchar>(data.rows(), data.cols(), true);

  for (int y = 0; y < input->height(); ++y) {
    for (int x = 0; x < input->width(); ++x) {
      imRef(input, x, y) = data(x, y);
    }
  }

  // Compute dt.
  image<float> *out = dt(input);
  delete input;

  Matrix result(data.rows(), data.cols());

  // Take square roots.
  for (int y = 0; y < out->height(); ++y) {
    for (int x = 0; x < out->width(); ++x) {
      result(x, y) = sqrt(imRef(out, x, y));
    }
  }

  return result;
}

} /* namespace */
