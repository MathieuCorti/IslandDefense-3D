//
// Created by wilmot_g on 03/05/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include "../helpers/Displayable.hpp"

class Island : public Displayable {
public:

  typedef struct s_vertex {
    s_vertex(Vector3f p, Vector3f n) : p(p), n(n) {}

    s_vertex(Vector3f p) : p(p) {}

    typedef std::shared_ptr<s_vertex> Ptr;

    Vector3f p;
    Vector3f n;
  } Vertex;

  typedef struct s_triangle {
    s_triangle(Vertex::Ptr v1, Vertex::Ptr v2, Vertex::Ptr v3, Vector3f n) : v1(v1),
                                                                             v2(v2),
                                                                             v3(v3),
                                                                             n(n) {}

    typedef std::shared_ptr<s_triangle> Ptr;

    Vertex::Ptr v1;
    Vertex::Ptr v2;
    Vertex::Ptr v3;
    Vector3f n;
  } Triangle;

  typedef std::vector<std::vector<Triangle::Ptr>> Triangles;

  typedef std::vector<std::vector<Vertex::Ptr>> Vertices;

  Island();

  void draw() const override;

private:

  Vector3f computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3);

  float islandPerlin(float x, float y) const;

  void generateTopTriangles();

  void generateBottomTriangles();

  void computePerVertexNormal();

  float _zmax, _xmax, _tess;
  Triangles _triangles;
  Vertices _vertices;
};

inline std::ostream &operator<<(std::ostream &os, const Island::Vertex &v) {
  os << v.p << "\t" << "\t" << v.n;
  return os;
}