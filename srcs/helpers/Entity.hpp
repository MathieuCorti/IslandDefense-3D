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
  Vector3f _angle;

public:

  explicit Entity(Vector3f &coordinates) : _coordinates(coordinates) {}

  Vector3f getCoordinates() const {
    return _coordinates;
  }

  Vector3f getAngle() const {
    return _angle;
  }

  void setCoordinates(const Vector3f &coordinates) {
    Entity::_coordinates = coordinates;
  }

  void setAngle(const Vector3f &angle) {
    Entity::_angle = angle;
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

  void setAngleX(float x) {
    Entity::_angle.x = x;
  }

  void setAngleY(float y) {
    Entity::_angle.y = y;
  }

  void setAngleZ(float z) {
    Entity::_angle.z = z;
  }
};