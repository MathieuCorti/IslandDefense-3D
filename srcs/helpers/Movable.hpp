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
  UP    , DOWN  , // X
  LEFT  , RIGHT , // Y
  FRONT , BACK    // Z
};

class Movable : public Displayable {
protected:
  float _speed;

public:
  Movable(float _speed, Vector3f coordinates);

  explicit Movable(float _speed);

  virtual void move(Direction direction);

  void moveTo(Vector3f& coordinates);

  float getSpeed() const;

  void setSpeed(int speed);
};

