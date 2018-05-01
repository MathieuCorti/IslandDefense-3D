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

class Shape;
typedef std::list<Shape> Shapes;

struct Coordinates {
  Coordinates(float x, float y, float z) : x(x), y(y), z(z) {}

  float x;
  float y;
  float z;
};

struct BoundingBox {
//  BoundingBox(const Coordinates &upperLeft, const Coordinates &lowerRight) : upperLeft(upperLeft),
//                                                                             lowerRight(lowerRight) {}

  Coordinates upperLeft;
  Coordinates lowerRight;
};

struct Shape {
private:

  static constexpr float defaultDelta = 0;

public:

  const float &_deltaX;
  const float &_deltaY;

  std::vector<Coordinates> parts;
  float size;
  GLenum mode;
  Color color;

  void applyColor() const {
    glColor4f(color.r, color.g, color.b, color.a);
  }

  explicit Shape(std::vector<Coordinates> parts = std::vector<Coordinates>(), GLenum mode = GL_POLYGON,
                 Color color = Color(1, 1, 1));

  explicit Shape(std::vector<Coordinates> parts, GLenum mode, const float &deltaX, const float &deltaY,
                 Color color = Color(1, 1, 1));

  explicit Shape(const float &deltaX, const float &deltaY, std::vector<Coordinates> parts = std::vector<Coordinates>(),
                 GLenum mode = GL_POLYGON, Color color = Color(1, 1, 1));

//  BoundingBox getBoundingBox() const {
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
//  }

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