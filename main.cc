#include <iostream>

#include "segment3d.hpp"

int main() {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 1, 0), Vector3D(0, 1, 2));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  switch (intersection.second) {
    case CrossingStatus::NO_CROSSING:
      std::cout << "No intersection" << std::endl;
      break;
    case CrossingStatus::CONCIDENT:
      std::cout << "Segments are concident" << std::endl;
      break;
    case CrossingStatus::CROSSING:
      std::cout << "Intersection point using matrix method: "
                << intersection.first.get_x() << ", "
                << intersection.first.get_y() << ", "
                << intersection.first.get_z() << std::endl;
      break;
  }

  return 0;
}
