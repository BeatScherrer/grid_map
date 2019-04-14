#pragma once

/** @file
 *
 *  Declaration of the LikelihoodField class.
 */

#include <grid_map_sdf/SignedDistanceField.hpp>

#include <vector>
#include <string>

namespace grid_map {

class LikelihoodField {
public:
    LikelihoodField() = default;
    ~LikelihoodField() = default;

  const Matrix& getData() const;

  void calculateLikelihoodField(const GridMap& gridMap, const std::string layer, const double sigma = 0);
  double getLikelihoodAt(const Vector& position) const;
  friend std::ostream& operator << (std::ostream &out, const LikelihoodField& in);

private:
  double sigma_;
  Matrix data_;
  Size size_;
  Length length_;
  Position position_;
  double resolution_;
};

} // namespace grid_map