//
// Created by wilmot_g on 03/05/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include "../helpers/Displayable.hpp"
#include "Cannon.hpp"

class Island : public Displayable, public Alive {
public:
  Island();

  void draw() const override;

  void update() override;

  Cannon::Ptr getCannon() const;

private:

  float islandPerlin(float x, float y) const;

  void generateTopTriangles(Color color);

  float _zmax, _xmax, _tess, _maxHeight, _minHeight;
  Vertices _vertices;
  Cannon::Ptr _cannon;
};