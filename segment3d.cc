#include "segment3d.hpp"

#include <Eigen/Dense>
#include <limits>
#include <stdexcept>

Segment3D::Segment3D(const Vector3D& start, const Vector3D& end)
    : start(start), end(end) {
  if (start.x == end.x && start.y == end.y && start.z == end.z) {
    throw std::invalid_argument(
        "Error: Segment start and end points are the same.");
  }

  // plane.AddRow({end.y - start.y, -(end.x - start.x), 0,
  //               start.x * (end.y - start.y) - start.y * (end.x -
  //               start.x)});
  // plane.AddRow({end.z - start.z, 0, -(end.x - start.x),
  //               start.x * (end.z - start.z) - start.z * (end.x -
  //               start.x)});
  // plane.AddRow({0, end.z - start.z, -(end.y - start.y),
  //               start.y * (end.z - start.z) - start.z * (end.y -
  //               start.y)});

  A << end.y - start.y, -(end.x - start.x), 0, end.z - start.z, 0,
      -(end.x - start.x), 0, end.z - start.z, -(end.y - start.y);

  b << start.x * (end.y - start.y) - start.y * (end.x - start.x),
      start.x * (end.z - start.z) - start.z * (end.x - start.x),
      start.y * (end.z - start.z) - start.z * (end.y - start.y);
}

std::pair<Vector3D, CrossingStatus> Segment3D::Intersect(
    const Segment3D& other_segment) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> merged_A(
      A.rows() + other_segment.A.rows(), A.cols());
  merged_A << A, other_segment.A;

  Eigen::VectorXd merged_b(b.rows() + other_segment.b.rows());
  merged_b << b, other_segment.b;

  Eigen::MatrixXd augmented_matrix(merged_A.rows(), merged_A.cols() + 1);
  augmented_matrix << merged_A, merged_b;

  if (3 == merged_A.fullPivLu().rank() &&
      3 == augmented_matrix.fullPivLu().rank()) {
    Eigen::VectorXd x = merged_A.fullPivLu().solve(merged_b);

    return std::make_pair(Vector3D(x(0), x(1), x(2)), CrossingStatus::CROSSING);
  }

  if (merged_A.fullPivLu().rank() < augmented_matrix.fullPivLu().rank()) {
    return std::make_pair(Vector3D(std::numeric_limits<double>::infinity(),
                                   std::numeric_limits<double>::infinity(),
                                   std::numeric_limits<double>::infinity()),
                          CrossingStatus::NO_CROSSING);
  } else {
    return std::make_pair(Vector3D(0, 0, 0), CrossingStatus::CONCIDENT);
  }

  return std::make_pair(Vector3D(std::numeric_limits<double>::infinity(),
                                 std::numeric_limits<double>::infinity(),
                                 std::numeric_limits<double>::infinity()),
                        CrossingStatus::NO_CROSSING);

  // plane.MergeMatrix(other_segment.plane);
  // int rank = plane.CalculateRankUsingMinors();
  // std::cout << "rank = " << rank << std::endl;

  // if (rank == 3) {
  //   std::vector<double> solve = plane.SolveLinearSystem();
  //   return Vector3D(solve[0], solve[1], solve[2]);
  // }
}

// Vector3D Segment3D::Intersect2(const Segment3D& other_segment) {
//   double x1 = start.x, y1 = start.y, z1 = start.z;
//   double x2 = end.x, y2 = end.y, z2 = end.z;
//   double x3 = other_segment.start.x, y3 = other_segment.start.y,
//          z3 = other_segment.start.z;
//   double x4 = other_segment.end.x, y4 = other_segment.end.y,
//          z4 = other_segment.end.z;

//   double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) /
//              ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
//   double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) /
//              ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

//   if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
//     double intersection_x = x1 + t * (x2 - x1);
//     double intersection_y = y1 + t * (y2 - y1);
//     double intersection_z = z1 + t * (z2 - z1);
//     return Vector3D(intersection_x, intersection_y, intersection_z);
//   } else {
//     std::cout << "No intersection" << std::endl;
//     Vector3D no_intersection(std::numeric_limits<double>::infinity(),
//                              std::numeric_limits<double>::infinity(),
//                              std::numeric_limits<double>::infinity());
//     return no_intersection;
//   }
// }