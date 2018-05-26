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
  LEFT  , RIGHT , // Y
  FORWARD , BACKWARD    // Z
};

class Movable : public Displayable {
protected:
  float _speed;

public:
  Movable(float _speed, Vector3f coordinates);

  explicit Movable(float _speed);

  virtual void move(Direction direction, int coef);

  void moveTo(Vector3f& coordinates);

  float getSpeed() const;

  void setSpeed(int speed);
};

