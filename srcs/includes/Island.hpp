//
// Created by wilmot_g on 03/05/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include "../helpers/Displayable.hpp"

class Island : public Displayable {
public:

  typedef std::vector<std::vector<std::pair<Vector3f, Vector3f>>> vertices;

  Island();

  void draw() const override;

private:

  Vector3f computeNormalPerlin(float i, float j);

  Vector3f computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3);

  float islandPerlin(float x, float y) const;

  float _zmax, _xmax, _tess;
  vertices _vertices;
};