//
//  Camera.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#pragma once

#include <cmath>
#include "../helpers/Glut.hpp"
#include "../helpers/Movable.hpp"
#include "../helpers/Displayable.hpp"

class Camera: public Movable {
private:
  float    _psi;
  float    _theta;
  float    _rotationSpeed;
  float    _translationSpeed;
  int      _time;
  int      _lastMouseX;
  int      _lastMouseY;
  int      _coef;

public:

  Camera();
  
  bool update() override;

  void draw() const override ;
  
  void move(Direction direction) override;

  void rotation(int x, int y);
  
  Vector3f getSight() const {
    return { _coordinates.x + sin(_theta) * sin(_psi),
             _coordinates.y + cos(_psi),
             _coordinates.z + cos(_theta)*sin(_psi) };
  }
};

