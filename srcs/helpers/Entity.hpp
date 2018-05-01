//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "Vector3f.hpp"
#include "Glut.hpp"

class Entity {
protected:
  Vector3f _coordinates;

public:

  explicit Entity(Vector3f& coordinates) : _coordinates(coordinates) {}

  Vector3f getCoordinates() const {
    return  _coordinates;
  }
  
  void setCoordinates(Vector3f& coordinates) {
    Entity::_coordinates = coordinates;
  }

  void setX(float x) {
    Entity::_coordinates.x = x;
  }

  void setY(float y) {
    Entity::_coordinates.y = y;
  }

  void setZ(float z) {
    Entity::_coordinates.z = z;
  }

};