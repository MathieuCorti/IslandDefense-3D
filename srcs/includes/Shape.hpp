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

struct BoundingBox {
  BoundingBox() = default;
  BoundingBox(const Vector3f &cubeMin, const Vector3f &cubeMax) : vecMin(cubeMin),
                                                                  vecMax(cubeMax) {}

  Vector3f vecMin;
  Vector3f vecMax;
};

struct Shape {
private:
  BoundingBox _boundingBox;
  static const Vector3f defaultDelta;
  const Vector3f &_delta;

public:
  Triangles _parts;
  float _size;
  GLenum _mode;
  Color _color;

  void applyColor() const;

  void computePerVertexNormal();

  explicit Shape(Triangles parts, GLenum mode = GL_TRIANGLES, Color color = BLACK);

  explicit Shape(Triangles parts, const Vector3f &delta, 
                 GLenum mode = GL_TRIANGLES, Color color = BLACK);
  
  bool collideWith(BoundingBox other) const;

  bool collideWith(Shape other) const;

  void generateBoundingBox();

  const BoundingBox &get_boundingBox() const;

};