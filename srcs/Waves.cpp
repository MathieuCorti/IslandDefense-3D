//
// Created by wilmot_g on 01/05/18.
//

#include "includes/Waves.hpp"
#include "helpers/Glut.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

Waves::Waves() {
  _tesselation = 16;
  _wavelength = (float) M_PI / 2;
  _amplitude = 0.1f;
  _time = 0.0f;
  _showTangeant = false;
  _showNormal = false;
  _showWireframe = false;
}

float Waves::computeHeight(float x) const {
  float k = 2 * (float) M_PI / _wavelength;
  float shift = _wavelength * _time;
  return _amplitude * std::sin(k * x + shift);
}

float Waves::computeSlope(float x) const {
  float k = 2 * (float) M_PI / _wavelength;
  float shift = _wavelength * _time;
  return _amplitude * k * std::cos(k * x + shift);
}

bool Waves::update() {
  _time += Game::getInstance().getDeltaTime();
  return false;
}

void Waves::draw() const {
  if (_showWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  glEnable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  float xStep = 2.0f / _tesselation;
  float zStep = 2.0f / _tesselation;

  for (int j = 0; j < _tesselation; j++) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1, 1, 1, 0.5);
    float z = -1.0f + j * zStep;
    for (int i = 0; i <= _tesselation; i++) {
      float x = -1.0f + i * xStep;
      float y = computeHeight(x);
      float dx = 1;
      float dy = computeSlope(x);
      glNormal3f(-dy, dx, 0);
      glVertex3f(x, y, z);
      glVertex3f(x, y, z + zStep);
    }
    glEnd();
  }

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (_showTangeant || _showNormal) {
    for (int j = 0; j < _tesselation; j++) {
      glBegin(GL_LINES);
      float z = -1.0f + j * zStep;
      for (int i = 0; i <= _tesselation; i++) {
        float x = -1.0f + i * xStep;
        float y = computeHeight(x);
        float dx = 1;
        float dy = computeSlope(x);

        if (_showTangeant) {
          glColor4f(0, 1, 1, 1);
          Axes::drawVector(Vector3f(x, y, z), Vector3f(dx, dy, 0), 0.1, true);
          Axes::drawVector(Vector3f(x, y, z + zStep), Vector3f(dx, dy, 0), 0.1, true);
        }

        if (_showNormal) {
          glColor4f(1, 1, 0, 1);
          Axes::drawVector(Vector3f(x, y, z), Vector3f(-dy, dx, 0), 0.1, true);
          Axes::drawVector(Vector3f(x, y, z + zStep), Vector3f(-dy, dx, 0), 0.1, true);
        }
      }
      glEnd();
    }
  }
}

void Waves::toggleTangeants() {
  _showTangeant = !_showTangeant;
}

void Waves::toggleNormals() {
  _showNormal = !_showNormal;
}

void Waves::toggleWireframe() {
  _showWireframe = !_showWireframe;
}

void Waves::doubleVertices() {
  Waves::_tesselation *= 2;
  _vertices.clear();
}

void Waves::halveSegments() {
  Waves::_tesselation /= 2;
  Waves::_tesselation = _tesselation < 4 ? 4 : _tesselation;
  _vertices.clear();
}
