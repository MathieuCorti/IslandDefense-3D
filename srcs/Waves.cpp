//
// Created by wilmot_g on 01/05/18.
//

#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

Waves::Waves() {
  _tesselation = 64;
  _wavelength = (float) M_PI / 2;
  _amplitude = 0.1f;
  _time = 0.0f;
  _showTangeant = false;
  _showNormal = false;
  _showWireframe = false;
}

float Waves::sineWave(float x, float z, float w, float a, float kx, float kz) const {
  kx /= w;
  kz /= w;
  float shift = w * _time / 4.0f;
  return a * std::sin(kx * x + kz * z + shift);
}

float Waves::computeHeight(float x, float z) const {
  return 0.5f * (sineWave(x, z, (float) M_PI / 2.0f, 1.0f / 8.0f, 2.0f * (float) M_PI, 1.0f * (float) M_PI) +
                 sineWave(x, z, (float) M_PI / 2.5f, 1.0f / 7.0f, 1.0f * (float) M_PI, 2.0f * (float) M_PI));
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

void Waves::drawDebug() const {
  float xStep = 2.0f / _tesselation;
  float zStep = 2.0f / _tesselation;

  if (_showTangeant || _showNormal) {
    for (int j = 0; j < _tesselation; j++) {
      glBegin(GL_LINES);
      float z = -1.0f + j * zStep;
      for (int i = 0; i <= _tesselation; i++) {
        float x = -1.0f + i * xStep;
        float y = computeHeight(x, z);
        float dx = 1.0f;
        float dy = computeSlope(x);

        if (_showTangeant) {
          glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
          Axes::drawVector(Vector3f(x, y, z), Vector3f(dx, dy, 0.0f), 0.1f, true);
          Axes::drawVector(Vector3f(x, y, z + zStep), Vector3f(dx, dy, 0.0f), 0.1f, true);
        }

        if (_showNormal) {
          glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
          Axes::drawVector(Vector3f(x, y, z), Vector3f(-dy, dx, 0.0f), 0.1f, true);
          Axes::drawVector(Vector3f(x, y, z + zStep), Vector3f(-dy, dx, 0.0f), 0.1f, true);
        }
      }
      glEnd();
    }
  }
}

void Waves::draw() const {
  if (_showWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  glEnable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  GLfloat pos[] = {0.0f, 1.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  GLfloat lightColorDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);

  GLfloat specular[] = {0.7f, 0.7f, 0.9f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 50.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  float xStep = 2.0f / _tesselation;
  float zStep = 2.0f / _tesselation;

  for (int j = 0; j < _tesselation; j++) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    float z = -1.0f + j * zStep;
    for (int i = 0; i <= _tesselation; i++) {
      float x = -1.0f + i * xStep;
      float dx = 1.0f;
      float dy = computeSlope(x);
      glNormal3f(-dy, dx, 0.0f);
      glVertex3f(x, computeHeight(x, z), z);
      glVertex3f(x, computeHeight(x, z + zStep), z + zStep);
    }
    glEnd();
  }

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  drawDebug();
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
