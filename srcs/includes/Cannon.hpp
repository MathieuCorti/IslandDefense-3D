//
// Created by wilmot_g on 24/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"
#include "Projectile.hpp"
#include "Pellet.hpp"

class Pellet;

class Cannon : public Displayable {
public:
  typedef std::shared_ptr<Cannon> Ptr;

  explicit Cannon(float rotation = 1.0f, float speed = 3.0f, float radius = 0.01, Color color = Color(0, 127, 255));

  void draw() const override;

  void setPos(float x, float y, float angle);

  void speed(float value);

  void rotation(float angle);

  Projectile::Ptr blast();

  std::shared_ptr<Pellet> defend();

  const Vector3f &getVelocity() const;

  float getScale() const;

private:
  void drawDirection() const;

  void drawTrajectory() const;

  float _rotation;
  float _speed;
  float _scale;
  float _radius;
  bool _inverted;
  Vector3f _velocity;
  float _lastFire, _lastDefence;
  Color _color;
};