#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <Eigen/Dense>

// #include "matrix.hpp"
#include "vector3d.hpp"

typedef enum CrossingStatus {
  NO_CROSSING = 0,
  CONCIDENT,
  CROSSING
} CrossingStatus;

class Segment3D {
 public:
  Segment3D(const Vector3D& start, const Vector3D& end);

  std::pair<Vector3D, CrossingStatus> Intersect(const Segment3D& other_segment);
  // Vector3D Intersect2(const Segment3D& other_segment);

 private:
  Vector3D start, end;
  // Matrix plane;
  Eigen::Matrix3d A;
  Eigen::Vector3d b;
};

#endif  // SEGMENT_HPP