//
//  Movable.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "Entity.hpp"
#include "Displayable.hpp"

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Movable : public Displayable {
protected:
  float _speed;

public:
  Movable(float _speed, float x, float y);

  explicit Movable(float _speed);

  virtual void move(Direction direction);

  void moveTo(float x, float y);

  float getSpeed() const;

  void setSpeed(int speed);
};

