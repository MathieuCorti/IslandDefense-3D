//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Shape.hpp"
#include "helpers/Alive.hpp"

void Displayable::draw() const {
  for (Shape shape: _shapes) {
    glBegin(shape.mode);
    shape.applyColor();
    for (Coordinates coordinates: shape.parts) {
      glVertex2d(coordinates.x + _x, coordinates.y + _y);
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
