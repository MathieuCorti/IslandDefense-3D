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

//struct BoundingBox {
//  BoundingBox(const Coordinates &upperLeft, const Coordinates &lowerRight) : upperLeft(upperLeft),
//                                                                             lowerRight(lowerRight) {}

//  Vector3f upperLeft;
//  Vector3f lowerRight;
//};

typedef struct s_vertex {
  s_vertex(Vector3f p, Vector3f n) : p(p), n(n) {}

  explicit s_vertex(Vector3f p) : p(p) {}

  typedef std::shared_ptr<s_vertex> Ptr;

  Vector3f p;
  Vector3f n;
} Vertex;

typedef std::vector<std::vector<Vertex::Ptr>> Vertices;

typedef struct s_triangle {
  s_triangle(Vertex::Ptr v1, Vertex::Ptr v2, Vertex::Ptr v3, Vector3f n) : v1(std::move(v1)),
                                                                           v2(std::move(v2)),
                                                                           v3(std::move(v3)),
                                                                           n(n) {}

  s_triangle(Vertex::Ptr v1, Vertex::Ptr v2, Vertex::Ptr v3) : v1(std::move(v1)),
                                                               v2(std::move(v2)),
                                                               v3(std::move(v3)) {}

  Vertex::Ptr v1;
  Vertex::Ptr v2;
  Vertex::Ptr v3;
  Vector3f n;

  static Vector3f computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
    Vector3f u = {p2.x - p1.x,
                  p2.y - p1.y,
                  p2.z - p1.z};
    Vector3f v = {p3.x - p1.x,
                  p3.y - p1.y,
                  p3.z - p1.z};
    Vector3f n = {u.y * v.z - u.z * v.y,
                  u.z * v.x - u.x * v.z,
                  u.x * v.y - u.y * v.x};
    return n.normalize().invert();
  }

  s_triangle &computeNormal() {
    Vector3f u = {v2->p.x - v1->p.x,
                  v2->p.y - v1->p.y,
                  v2->p.z - v1->p.z};
    Vector3f v = {v3->p.x - v1->p.x,
                  v3->p.y - v1->p.y,
                  v3->p.z - v1->p.z};
    n = {u.y * v.z - u.z * v.y,
                  u.z * v.x - u.x * v.z,
                  u.x * v.y - u.y * v.x};
    n.normalize();
    n.invert();
    return *this;
  }

} Triangle;

typedef std::vector<Triangle> Triangles;

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