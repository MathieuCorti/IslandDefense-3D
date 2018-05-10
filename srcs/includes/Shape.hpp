//
//  Shape.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

#include "../helpers/Glut.hpp"

#include <list>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../helpers/Displayable.hpp"
#include "../helpers/Color.hpp"
#include "Config.hpp"
#include "../helpers/Triangle.h"

class Shape;

typedef std::list<Shape> Shapes;

//struct BoundingBox {
//  BoundingBox(const Coordinates &upperLeft, const Coordinates &lowerRight) : upperLeft(upperLeft),
//                                                                             lowerRight(lowerRight) {}

//  Vector3f upperLeft;
//  Vector3f lowerRight;
//};

struct Shape {
private:

public:
  Triangles _parts;
  float _size;
  GLenum _mode;
  Color _color;

  void applyColor() const;

  void computePerVertexNormal();

  explicit Shape(Triangles triangle, GLenum mode = GL_TRIANGLES, Color color = BLACK);

  // TODO : New Bounding box in 3D
//  BoundingBox getBoundingBox() const {}

  // TODO : New Collide with box in 3D
//  bool collideWith(BoundingBox bb) const {}

  // TODO : New Collide box in 3D
//  static bool collide(const Shapes shapes1, const Shapes shapes2) {}
};