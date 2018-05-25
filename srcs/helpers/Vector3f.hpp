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
#include <GL/gl.h>
#include <cstring>
#include <iomanip>

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

  Vector3f operator*(const float m[16]) const {
    float px = x * m[0] + y * m[4] + z * m[8] + m[12];
    float py = x * m[1] + y * m[5] + z * m[9] + m[13];
    float pz = x * m[2] + y * m[6] + z * m[10] + m[14];
    float pw = x * m[3] + y * m[7] + z * m[11] + m[15];
    return {px / pw, py / pw, pz / pw};
  }

  Vector3f operator+(const Vector3f &v2) const {
    return {x + v2.x, y + v2.y, z + v2.z};
  }

  static Vector3f cross(const Vector3f &v1, const Vector3f &v2) {
    return {(v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)};
  }

  float *toRotationMatrix(float *m) const {
    float cx = std::cos(x);
    float sx = std::sin(x);
    float cy = std::cos(-y);
    float sy = std::sin(-y);
    float cz = std::cos(z);
    float sz = std::sin(z);

    float cxsy = cx * sy;
    float sxsy = sx * sy;

    m[0] = cy * cz;
    m[4] = -cy * sz;
    m[8] = -sy;
    m[1] = -sxsy * cz + cx * sz;
    m[5] = sxsy * sz + cx * cz;
    m[9] = -sx * cy;
    m[2] = cxsy * cz + sx * sz;
    m[6] = -cxsy * sz + sx * cz;
    m[10] = cx * cy;

    m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
    return m;
  }

  float *toTranslationMatrix(float *m) const {
    m[0] = 1.0f;
    m[4] = 0.0f;
    m[8] = 0.0f;
    m[12] = x;
    m[1] = 0.0f;
    m[5] = 1.0f;
    m[9] = 0.0f;
    m[13] = y;
    m[2] = 0.0f;
    m[6] = 0.0f;
    m[10] = 1.0f;
    m[14] = z;
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = 1.0f;
    return m;
  }

  static void multMatrix(const float *m2, const float *m1, float *result) {
    result[0] = m1[0] * m2[0] + m1[1] * m2[4] + m1[2] * m2[8] + m1[3] * m2[12];
    result[1] = m1[0] * m2[1] + m1[1] * m2[5] + m1[2] * m2[9] + m1[3] * m2[13];
    result[2] = m1[0] * m2[2] + m1[1] * m2[6] + m1[2] * m2[10] + m1[3] * m2[14];
    result[3] = m1[0] * m2[3] + m1[1] * m2[7] + m1[2] * m2[11] + m1[3] * m2[15];
    result[4] = m1[4] * m2[0] + m1[5] * m2[4] + m1[6] * m2[8] + m1[7] * m2[12];
    result[5] = m1[4] * m2[1] + m1[5] * m2[5] + m1[6] * m2[9] + m1[7] * m2[13];
    result[6] = m1[4] * m2[2] + m1[5] * m2[6] + m1[6] * m2[10] + m1[7] * m2[14];
    result[7] = m1[4] * m2[3] + m1[5] * m2[7] + m1[6] * m2[11] + m1[7] * m2[15];
    result[8] = m1[8] * m2[0] + m1[9] * m2[4] + m1[10] * m2[8] + m1[11] * m2[12];
    result[9] = m1[8] * m2[1] + m1[9] * m2[5] + m1[10] * m2[9] + m1[11] * m2[13];
    result[10] = m1[8] * m2[2] + m1[9] * m2[6] + m1[10] * m2[10] + m1[11] * m2[14];
    result[11] = m1[8] * m2[3] + m1[9] * m2[7] + m1[10] * m2[11] + m1[11] * m2[15];
    result[12] = m1[12] * m2[0] + m1[13] * m2[4] + m1[14] * m2[8] + m1[15] * m2[12];
    result[13] = m1[12] * m2[1] + m1[13] * m2[5] + m1[14] * m2[9] + m1[15] * m2[13];
    result[14] = m1[12] * m2[2] + m1[13] * m2[6] + m1[14] * m2[10] + m1[15] * m2[14];
    result[15] = m1[12] * m2[3] + m1[13] * m2[7] + m1[14] * m2[11] + m1[15] * m2[15];
  }

  static void printMatrix(const float m[16]) {
    std::cout << std::fixed << std::setprecision(5);
    for (int i = 0; i < 16; i) {
      std::cout << m[i] << (m[i] >= 0 ? " " : "") << "\t";
      if (++i % 4 == 0) {
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }

  float x;
  float y;
  float z;
};

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v) {
  os << v.x << " " << v.y << " " << v.z;
  return os;
}