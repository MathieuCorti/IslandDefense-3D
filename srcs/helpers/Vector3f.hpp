//
//  Vector3f.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#pragma once

#include <cmath>
#include <ostream>
#include <iostream>

struct Vector3f {
  Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

  Vector3f() : x(0), y(0), z(0) {}

  Vector3f &normalize() {
    float magnitude = std::sqrt(x * x + y * y + z * z);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    return *this;
  }

  Vector3f &invert() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
  }

  Vector3f operator*(const float n) const {
    return {x * n, y * n, z * n};
  }

  Vector3f operator+(const Vector3f &v2) const {
    return {x + v2.x, y + v2.y, z + v2.z};
  }

  static Vector3f cross(const Vector3f &v1, const Vector3f &v2) {
    return {(v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)};
  }

  static float dot(const Vector3f &v1, const Vector3f &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  Vector3f rotate(const Vector3f &k, float theta) {
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);
    Vector3f a = *this * cosTheta;
    Vector3f b = cross(k, *this) * sinTheta;
    Vector3f c = (k * dot(k, *this)) * (1.0f - cosTheta);
    return a + b + c;
  }

  static Vector3f transform(Vector3f transformation, const Vector3f &angle) {
    transformation = transformation.rotate(Vector3f(1.0f, 0.0f, 0.0f), static_cast<float>(angle.x * M_PI / 180.0f));
    transformation = transformation.rotate(Vector3f(0.0f, 1.0f, 0.0f), static_cast<float>(angle.y * M_PI / 180.0f));
    transformation = transformation.rotate(Vector3f(0.0f, 0.0f, 1.0f), static_cast<float>(angle.z * M_PI / 180.0f));
    return transformation;
  }

  float x;
  float y;
  float z;
};

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v) {
  os << v.x << " " << v.y << " " << v.z;
  return os;
}