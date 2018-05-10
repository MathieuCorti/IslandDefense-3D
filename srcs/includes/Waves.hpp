//
// Created by wilmot_g on 01/05/18.
//

#pragma once

#include <vector>
#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:

  Waves();

  void draw() const override;

  void update() override;

  static float computeHeight(float x, float z);

  static float computeSlope(float x, float z);

  static float maxHeight();

  void doubleVertices();

  void halveSegments();

  void toggleAnimation();

  static float _time;
  static float _maxHeight;

private:

  static float sineNormal(float x, float z, float wavelength, float amplitude, float kx, float kz);

  static float sineWave(float x, float z, float wavelength, float amplitude, float kx, float kz);

  bool _animate;
  Vertices _vertices;
  int _tess;
};