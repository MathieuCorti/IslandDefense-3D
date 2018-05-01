//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Movable.hpp"

Movable::Movable(float _speed, Vector3f coordinates) : Displayable(coordinates), _speed(_speed) {}

Movable::Movable(float _speed) : _speed(_speed) {}

void Movable::move(Direction direction) {
  switch (direction) {
    case UP:
      setY(getCoordinates().y + getSpeed());
      break;
    case DOWN:
      setY(getCoordinates().y - getSpeed());
      break;
    case LEFT:
      setX(getCoordinates().x - getSpeed());
      break;
    case RIGHT:
      setX(getCoordinates().x + getSpeed());
      break;
    case FRONT:
      setZ(getCoordinates().z + getSpeed());
      break;
    case BACK:
      setZ(getCoordinates().z - getSpeed());
      break;
  }
}

void Movable::moveTo(Vector3f& coordinates) {
  setCoordinates(coordinates);
}

float Movable::getSpeed() const {
  return _speed;
}

void Movable::setSpeed(int speed) {
  Movable::_speed = speed;
}
