/** @file
 *
 *  Definition of the LikelihoodField class.
 */

#include "grid_map_lf/LikelihoodField.h"

#include <grid_map_core/GridMapMath.hpp>

#include <boost/math/distributions/normal.hpp>
#include <cmath>

namespace grid_map {

void LikelihoodField::setData(const grid_map::GridMap& grid_map, const std::string layer)
{
  data_ = grid_map[layer];
  size_ = grid_map.getSize();
  length_ = grid_map.getLength();
  position_ = grid_map.getPosition();
  resolution_ = grid_map.getResolution();
}

const Matrix& LikelihoodField::getData() const
{
  return data_;
}

void LikelihoodField::calculateLikelihoodField(const GridMap& gridMap,
                                               const std::string layer,
                                               const double sigma)
{
  if(sigma == 0)
  {
    throw std::domain_error("Standard deviation of 0 is not allowed");
  }

  boost::math::normal_distribution<double> normalDistribution(0, sigma);
  double normalization = pdf(normalDistribution, 0);

  // set properties
  resolution_ = gridMap.getResolution();
  size_ = gridMap.getSize();
  length_ = gridMap.getLength();
  position_ = gridMap.getPosition();

  // Size the Matrix and set to zero
  data_.resize(size_(0), size_(1));
  data_.setZero();

  const auto& data = gridMap[layer];

  std::cout << data << std::endl;

  for (std::size_t i = 0; i < size_(0); ++i)
  {
    for (std::size_t j = 0; j < size_(1); ++j)
    {
      // if unknown, set likelihood to 0.5
      if(isnan(data(i, j)))
      {
        data_(i, j) = 0.5;
      }
      else
      {
        data_(i, j) = pdf(normalDistribution, data(i, j))/normalization;
      }
    }
  }
}

double LikelihoodField::getLikelihoodAt(const Vector& position) const
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

std::ostream& operator<< (std::ostream& out, const LikelihoodField& in)
{
  out << in.data_ << std::endl;
  return out;
}

} // namespace grid_map

