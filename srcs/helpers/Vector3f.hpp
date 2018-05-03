//
//  Vector3f.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#pragma once

#include <ostream>

struct Vector3f {
  Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

  Vector3f() : x(0), y(0), z(0) {}

  float x;
  float y;
  float z;
};

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v) {
  os << v.x << " " << v.y <<  " " << v.z;
  return os;
}