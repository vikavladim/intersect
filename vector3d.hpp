#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector3D {
 public:
  Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

  double get_x() const { return x; }
  double get_y() const { return y; }
  double get_z() const { return z; }

  friend class Segment3D;

 private:
  double x, y, z;
};

#endif  // VECTOR_HPP