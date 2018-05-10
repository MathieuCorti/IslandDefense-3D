//
// Created by wilmot_g on 10/05/18.
//

#pragma once

#include <vector>
#include <memory>
#include "Vector3f.hpp"

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

  static void subdivide(s_triangle t, int n, std::vector<s_triangle> &result) {
    if (n == 0) {
      result.push_back(t.computeNormal());
    } else {
      Vertex::Ptr v12 = std::make_shared<Vertex>(Vector3f(0.5f * (t.v1->p.x + t.v2->p.x),
                                                          0.5f * (t.v1->p.y + t.v2->p.y),
                                                          0.5f * (t.v1->p.z + t.v2->p.z)));
      Vertex::Ptr v13 = std::make_shared<Vertex>(Vector3f(0.5f * (t.v1->p.x + t.v3->p.x),
                                                          0.5f * (t.v1->p.y + t.v3->p.y),
                                                          0.5f * (t.v1->p.z + t.v3->p.z)));
      Vertex::Ptr v23 = std::make_shared<Vertex>(Vector3f(0.5f * (t.v2->p.x + t.v3->p.x),
                                                          0.5f * (t.v2->p.y + t.v3->p.y),
                                                          0.5f * (t.v2->p.z + t.v3->p.z)));

      subdivide(s_triangle(t.v1, v12, v13, t.n), n - 1, result);
      subdivide(s_triangle(v12, t.v2, v23, t.n), n - 1, result);
      subdivide(s_triangle(v13, v23, t.v3, t.n), n - 1, result);
      subdivide(s_triangle(v12, v23, v13, t.n), n - 1, result);
    }
  }

  void subdivide(int n, std::vector<s_triangle> &result) {
    subdivide(*this, n, result);
  }
} Triangle;

typedef std::vector<Triangle> Triangles;