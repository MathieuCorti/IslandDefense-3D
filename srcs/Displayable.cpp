//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Shape.hpp"
#include "helpers/Alive.hpp"

void Displayable::draw() const {
  for (Shape shape: _shapes) {
    glBegin(shape.mode);
    shape.applyColor();
    for (Vector3f coordinates: shape.parts) {
      glVertex3d(coordinates.x + _coordinates.x, coordinates.y + _coordinates.z, coordinates.z + _coordinates.z);
    }
    glEnd();
  }
}

const Shapes &Displayable::getShapes() const {
  return _shapes;
}

const std::list<Displayable *> &Displayable::getCollidables() {
  return _collidables;
}
