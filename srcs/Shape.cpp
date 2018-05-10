//
// Created by wilmot_g on 02/04/18.
//

#include <utility>
#include "helpers/Shape.hpp"

Shape::Shape(Triangles parts, GLenum mode, Color color) : _color(color),
                                                         _parts(std::move(parts)),
                                                         _mode(mode),
                                                         _size(1) {}

void Shape::applyColor() const {
  glColor4f(_color.r, _color.g, _color.b, _color.a);
}

void Shape::computePerVertexNormal() {
  for (const Triangle &t : _parts) {
    t.v1->n.x += t.n.x;
    t.v1->n.y += t.n.y;
    t.v1->n.z += t.n.z;
    t.v2->n.x += t.n.x;
    t.v2->n.y += t.n.y;
    t.v2->n.z += t.n.z;
    t.v3->n.x += t.n.x;
    t.v3->n.y += t.n.y;
    t.v3->n.z += t.n.z;
  }
  for (const Triangle &t : _parts) {
    t.v1->n.normalize();
    t.v2->n.normalize();
    t.v3->n.normalize();
  }
}
