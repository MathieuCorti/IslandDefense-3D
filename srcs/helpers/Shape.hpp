//
//  Shape.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

#include "Glut.hpp"

#include <list>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Displayable.hpp"
#include "Color.hpp"
#include "../includes/Config.hpp"

class Shape;
typedef std::list<Shape> Shapes;

struct BoundingBox {
//  BoundingBox(const Coordinates &upperLeft, const Coordinates &lowerRight) : upperLeft(upperLeft),
//                                                                             lowerRight(lowerRight) {}

  Vector3f upperLeft;
  Vector3f lowerRight;
};

struct Shape {
private:

  static constexpr float defaultDelta = 0;

public:

  const float &_deltaX;
  const float &_deltaY;

  std::vector<Vector3f> parts;
  float size;
  GLenum mode;
  Color color;

  void applyColor() const {
    glColor4f(color.r, color.g, color.b, color.a);
  }

  explicit Shape(std::vector<Vector3f> parts = std::vector<Vector3f>(), GLenum mode = GL_POLYGON,
                 Color color = BLACK);

  explicit Shape(std::vector<Vector3f> parts, GLenum mode, const float &deltaX, const float &deltaY,
                 Color color = BLACK);

  explicit Shape(const float &deltaX, const float &deltaY, std::vector<Vector3f> parts = std::vector<Vector3f>(),
                 GLenum mode = GL_POLYGON, Color color = BLACK);

  // TODO : New Bounding box in 3D
  BoundingBox getBoundingBox() const {
//    auto xExtremes = std::minmax_element(parts.begin(), parts.end(),
//                                         [](const Coordinates &lhs, const Coordinates &rhs) {
//                                           return lhs.x > rhs.x;
//                                         });
//    auto yExtremes = std::minmax_element(parts.begin(), parts.end(),
//                                         [](const Coordinates &lhs, const Coordinates &rhs) {
//                                           return lhs.y > rhs.y;
//                                         });
//
//    return BoundingBox(Coordinates(xExtremes.first->x + _deltaX, yExtremes.first->y + _deltaY),
//                       Coordinates(xExtremes.second->x + _deltaX, yExtremes.second->y + _deltaY));
  }

  // TODO : New Collide with box in 3D
//  bool collideWith(BoundingBox bb) const {
//    BoundingBox bb1 = getBoundingBox();
//    BoundingBox bb2 = bb;
//
//    return bb1.upperLeft.x > bb2.lowerRight.x && bb1.lowerRight.x < bb2.upperLeft.x &&
//           bb1.upperLeft.y > bb2.lowerRight.y && bb1.lowerRight.y < bb2.upperLeft.y;
//  }
//
//  bool collideWith(const Shape &shape) const {
//    return collideWith(shape.getBoundingBox());
//  }
//  
  
  // TODO : New Collide box in 3D
//  static bool collide(const Shapes shapes1, const Shapes shapes2) {
//    for (const auto &shape1: shapes1) {
//      for (const auto &shape2: shapes2) {
//        if (shape1.collideWith(shape2)) {
//          return  true;
//        }
//      }
//    }
//    return false;
//  }

};

typedef std::list<Shape> Shapes;