//
// Created by wilmot_g on 01/04/18.
//

#pragma once

#include "../helpers/Axes.hpp"
#include "../helpers/Alive.hpp"

class Pellet : public Displayable, public Alive {
public:
  //Typedef
  typedef std::shared_ptr<Pellet> Ptr;

  explicit Pellet(float, Vector3f, Vector3f, float, Color c = Color(255, 0, 0));

  void updateShape();

  void update() override;

  void draw() const override;

private:
  float _radius;
  Color _color;
  float _startT;
  float _rotation;
};