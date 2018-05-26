//
// Created by wilmot_g on 24/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"
#include "Projectile.hpp"
#include "Pellet.hpp"
#include "Entities.hpp"

class Pellet;

class Cannon : public Displayable {
public:
  typedef std::shared_ptr<Cannon> Ptr;

  explicit Cannon(float speed = 3.0f, float radius = 0.01, Color color = Color(0, 127, 255));

  void draw() const override;

  void setCoordinates(Vector3f coordinates);

  void setRotation(float angle);

  void setAngle(Vector3f angle);

  void update() override;

  void speed(float value);

  void rotation(float angle);

  void blast();

  void defend();

private:
  void drawTrajectory() const;

  float _speed;
  float _radius;
  float _rotation;
  Vector3f _velocity;
  float _lastFire, _lastDefence;
  Color _color;
  Entities<Projectile> _projectiles;
  Entities<Pellet> _defences;
};