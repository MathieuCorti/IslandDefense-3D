//
// Created by wilmot_g on 03/05/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include "../helpers/Displayable.hpp"

class Island : public Displayable {
public:
  Island();

  void draw() const override;

private:

  float islandPerlin(float x, float y) const;

  void generateTopTriangles();

  float _zmax, _xmax, _tess;
  Vertices _vertices;
};

inline std::ostream &operator<<(std::ostream &os, const Vertex &v) {
  os << v.p << "\t" << "\t" << v.n;
  return os;
}