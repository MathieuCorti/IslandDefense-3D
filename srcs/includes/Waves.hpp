//
// Created by wilmot_g on 01/05/18.
//

#pragma once

#include <vector>
#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:

  typedef std::vector<std::vector<std::pair<Vector3f, Vector3f>>> vertices;

  Waves();

  void draw() const override;

  void update() override;

  static float computeHeight(float x, float z);

  static float computeSlope(float x, float z);

  static float maxHeight();

  void doubleVertices();

  void halveSegments();

  static float _wavelength;
  static float _amplitude;
  static float _time;
  static float _maxHeight;

private:

  static float sineNormal(float x, float z, float wavelength, float amplitude, float kx, float kz);

  static float sineWave(float x, float z, float wavelength, float amplitude, float kx, float kz);

  void drawDebug() const;

  void drawWaves() const;

  vertices _vertices;
  int _tesselation;
};