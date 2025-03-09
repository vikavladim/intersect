#include <gtest/gtest.h>

#include "segment3d.hpp"

TEST(Segment3DTest, ParalallelSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 1, 0), Vector3D(0, 1, 2));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::NO_CROSSING);
}

TEST(Segment3DTest, DegenerateSegment) {
  EXPECT_THROW(Segment3D segment2(Vector3D(0, 0, 0), Vector3D(0, 0, 0)),
               std::invalid_argument);
}

TEST(Segment3DTest, IntersectingSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 0, 0), Vector3D(0, 1, 0));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::CROSSING);

  ASSERT_EQ(intersection.first.get_x(), 0);
  ASSERT_EQ(intersection.first.get_y(), 0);
  ASSERT_EQ(intersection.first.get_z(), 0);
}

TEST(Segment3DTest, SecantSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(1, 0, 0), Vector3D(1, 1, 0));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::NO_CROSSING);
}

TEST(Segment3DTest, CondirectionalConsidentSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 0, 0), Vector3D(0, 0, 2));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::CONCIDENT);
}

TEST(Segment3DTest, ContinuingConsidentSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 0, 2), Vector3D(0, 0, 3));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::CONCIDENT);
}

TEST(Segment3DTest, CounterdirectionalConsidentSegments) {
  Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
  Segment3D segment2(Vector3D(0, 0, 0), Vector3D(0, 0, -2));

  std::pair<Vector3D, CrossingStatus> intersection =
      segment1.Intersect(segment2);

  ASSERT_EQ(intersection.second, CrossingStatus::CONCIDENT);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}