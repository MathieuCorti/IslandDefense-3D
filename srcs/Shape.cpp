//
// Created by wilmot_g on 02/04/18.
//

#include <utility>
#include <vector>
#include "includes/Shape.hpp"

const Vector3f Shape::defaultDelta = Vector3f();

Shape::Shape(Triangles parts, GLenum mode, Color color) : _delta(defaultDelta),
                                                          _color(color),
                                                         _parts(std::move(parts)),
                                                         _mode(mode),
                                                         _size(1) {}

Shape::Shape(Triangles parts, 
             const Vector3f &delta, 
             GLenum mode, Color color) : _delta(delta),
                                         _color(color),
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

void Shape::generateBoundingBox() {
  std::vector<Vector3f> triangleParts;
  for (auto& triangle: _parts) {
    triangleParts.emplace_back(triangle.v1->p);
  }
  
  // TODO: Remove duplicates

  auto xExtremes = std::minmax_element(triangleParts.begin(), triangleParts.end(),
                                       [](const Vector3f &lhs, const Vector3f &rhs) {
                                         return lhs.x > rhs.x;
                                       });
  auto yExtremes = std::minmax_element(triangleParts.begin(), triangleParts.end(),
                                       [](const Vector3f &lhs, const Vector3f &rhs) {
                                         return lhs.y > rhs.y;
                                       });
  auto zExtremes = std::minmax_element(triangleParts.begin(), triangleParts.end(),
                                       [](const Vector3f &lhs, const Vector3f &rhs) {
                                         return lhs.z > rhs.z;
                                       });

  _boundingBox = BoundingBox(Vector3f(xExtremes.first->x, yExtremes.first->y, zExtremes.first->z), 
    Vector3f(xExtremes.second->x, yExtremes.second->y, zExtremes.first->z));
}

bool Shape::collideWith(Shape other) const {
  return Shape::collideWith(other.get_boundingBox());
}

bool Shape::collideWith(BoundingBox other) const {
  
  BoundingBox own = get_boundingBox();
  std::cout << "Own bounding box : " << std::endl;
  std::cout << " - vecMax -> x: " << own.vecMax.x << " | y: " << own.vecMax.y << " | z: " << own.vecMax.z << std::endl;
  std::cout << " - vecMax -> x: " << own.vecMin.x << " | y: " << own.vecMin.y << " | z: " << own.vecMin.z << std::endl;
  std::cout << "Other bounding box : " << std::endl;
  std::cout << " - vecMax -> x: " << other.vecMax.x << " | y: " << other.vecMax.y << " | z: " << other.vecMax.z << std::endl;
  std::cout << " - vecMax -> x: " << other.vecMin.x << " | y: " << other.vecMin.y << " | z: " << other.vecMin.z << std::endl;
  
  // AABBtoAABB
  return(own.vecMax.x > other.vecMin.x &&
         own.vecMin.x < other.vecMax.x &&
         own.vecMax.y > other.vecMin.y &&
         own.vecMin.y < other.vecMax.y &&
         own.vecMax.z > other.vecMin.z &&
         own.vecMin.z < other.vecMax.z);
}

const BoundingBox &Shape::get_boundingBox() const {

  return BoundingBox(Vector3f(_boundingBox.vecMin.x + _delta.x,
                              _boundingBox.vecMin.y + _delta.y,
                              _boundingBox.vecMin.z + _delta.z),
                     Vector3f(_boundingBox.vecMax.x + _delta.x,
                              _boundingBox.vecMax.y + _delta.y,
                              _boundingBox.vecMax.z + _delta.z));
}
