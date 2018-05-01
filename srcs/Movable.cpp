//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Movable.hpp"

Movable::Movable(float _speed, float x, float y) : Displayable(x, y), _speed(_speed) {}

void Movable::move(Direction direction) {
  switch (direction) {
    case UP:
      setY(getY() + getSpeed());
      break;
    case DOWN:
      setY(getY() - getSpeed());
      break;
    case LEFT:
      setX(getX() - getSpeed());
      break;
    case RIGHT:
      setX(getX() + getSpeed());
      break;
  }
}

void Movable::moveTo(float x, float y) {
  setX(x);
  setY(y);
}

Movable::Movable(float _speed) : _speed(_speed) {}

float Movable::getSpeed() const {
  return _speed;
}

void Movable::setSpeed(int speed) {
  Movable::_speed = speed;
}
