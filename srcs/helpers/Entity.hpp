//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

class Entity {
protected:
  float _x;
  float _y;

public:

  explicit Entity(float x = 0, float y = 0) : _x(x), _y(y) {}

  float getX() const {
    return _x;
  }

  void setX(float x) {
    Entity::_x = x;
  }

  float getY() const {
    return _y;
  }

  void setY(float y) {
    Entity::_y = y;
  }

};