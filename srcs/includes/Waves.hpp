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

  bool update() override;

  float computeHeight(float x, float z) const;

  float computeSlope(float x) const;

  void toggleTangeants();

  void toggleNormals();

  void toggleWireframe();

  void doubleVertices();

  void halveSegments();

  typedef std::vector<Vector3f> vertices;

private:

  float sineWave(float x, float z, float wavelength, float amplitude, float kx, float kz) const;

  void drawDebug() const;

  vertices _vertices;
  int _tesselation;
  float _wavelength;
  float _amplitude;
  float _time;
  bool _showTangeant;
  bool _showNormal;
  bool _showWireframe;
};