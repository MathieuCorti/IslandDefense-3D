//
// Created by wilmot_g on 03/05/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include "../helpers/Displayable.hpp"

class Island : public Displayable {
public:

  typedef struct s_triangle {
    s_triangle(Vector3f p1, Vector3f p2, Vector3f p3, Vector3f n) : p1(p1), p2(p2), p3(p3), n(n) {}

    Vector3f p1;
    Vector3f p2;
    Vector3f p3;
    Vector3f n;
  } triangle;
  typedef std::vector<triangle> triangles;

  Island();

  void draw() const override;

private:

  Vector3f computeNormalPerlin(float i, float j);

  Vector3f computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3);

  float islandPerlin(float x, float y) const;

  float _zmax, _xmax, _tess;
  triangles _triangle;
};