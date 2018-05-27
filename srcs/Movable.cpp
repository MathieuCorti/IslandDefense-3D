//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Movable.hpp"

Movable::Movable(float _speed, Vector3f coordinates) : Displayable(coordinates), _speed(_speed) {}

Movable::Movable(float _speed) : _speed(_speed) {}

void Movable::move(Direction direction, int coef) {
  switch (direction) {
    case LEFT:
      setX(getCoordinates().x - getSpeed() * coef);
      break;
    case RIGHT:
      setX(getCoordinates().x + getSpeed() * coef);
      break;
    case FORWARD:
      setZ(getCoordinates().z + getSpeed() * coef);
      break;
    case BACKWARD:
      setZ(getCoordinates().z - getSpeed() * coef);
      break;
  }
}

void Movable::moveTo(Vector3f &coordinates) {
  setCoordinates(coordinates);
}

float Movable::getSpeed() const {
  return _speed;
}

void Movable::setSpeed(int speed) {
  Movable::_speed = speed;
}
