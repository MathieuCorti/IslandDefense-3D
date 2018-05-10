//
// Created by wilmot_g on 23/03/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include <cmath>
#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"
#include "../helpers/Alive.hpp"

extern const float g;

class Projectile : public Displayable, public Alive {
public:
  //Typedef
  typedef std::shared_ptr<Projectile> Ptr;

  explicit Projectile(float, Vector3f, Vector3f, Color c = Color(255, 0, 0));

  void update() override;

  void draw() const override;

  static Shape getCircle(float, Vector3f);

private:
  Color _color;
  float _startT;
  Vector3f _start;
  Vector3f _startVelocity, _velocity;
};