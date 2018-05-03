//
// Created by wilmot_g on 01/05/18.
//

#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

float Waves::_wavelength = (float) M_PI / 2;
float Waves::_amplitude = 0.1f;
float Waves::_time = 0.0f;
float Waves::_maxHeight = 0.0f;

Waves::Waves() {
  _tesselation = 64;
  _showTangeant = false;
  _showNormal = false;
  update();
}

float Waves::maxHeight() {
  return _maxHeight;
}

float Waves::sineWave(float x, float z, float w, float a, float kx, float kz) {
  kx /= w;
  kz /= w;
  float shift = w * _time / 4.0f;
  return a * std::sin(kx * x + kz * z + shift);
}

float Waves::computeHeight(float x, float z) {
  return 0.5f * (sineWave(x, z, (float) M_PI / 2.0f, 1.0f / 8.0f, 2.0f * (float) M_PI, 1.0f * (float) M_PI) +
                 sineWave(x, z, (float) M_PI / 2.5f, 1.0f / 7.0f, 1.0f * (float) M_PI, 2.0f * (float) M_PI));
}


float Waves::sineNormal(float x, float z, float w, float a, float kx, float kz) {
  kx /= w;
  kz /= w;
  float shift = w * _time / 4.0f;
  return a * (kx + kz) / 2 * std::cos(kx * x + kz * z + shift);
}

float Waves::computeSlope(float x, float z) {
  return 0.5f * (sineNormal(x, z, (float) M_PI / 2.0f, 1.0f / 8.0f, 2.0f * (float) M_PI, 1.0f * (float) M_PI) +
                 sineNormal(x, z, (float) M_PI / 2.5f, 1.0f / 7.0f, 1.0f * (float) M_PI, 2.0f * (float) M_PI));
}

bool Waves::update() {
  _time += Game::getInstance().getDeltaTime();

  float xStep = 2.0f / _tesselation;
  float zStep = 2.0f / _tesselation;

  _vertices.clear();
  for (int j = 0; j < _tesselation; j++) {
    float z = -1.0f + j * zStep;
    std::vector<std::pair<Vector3f, Vector3f>> row;
    for (int i = 0; i <= _tesselation; i++) {
      float x = -1.0f + i * xStep;
      float dx = 1.0f;
      float dy = computeSlope(x, z);
      float y = computeHeight(x, z);
      float y2 = computeHeight(x, z + zStep);
      row.emplace_back(Vector3f(x, y2, z + zStep), Vector3f(-dy, dx, 0)); //Point
      row.emplace_back(Vector3f(x, y, z), Vector3f(-dy, dx, 0)); //Normal
      _maxHeight = std::max(_maxHeight, y);
      _maxHeight = std::max(_maxHeight, y2);
    }
    _vertices.push_back(row);
  }

  return false;
}

void Waves::drawDebug() const {
  if (_showTangeant || _showNormal) {
    glBegin(GL_LINES);
    for (auto row : _vertices) {
      for (auto pair : row) {
        if (_showTangeant) {
          glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
          Axes::drawVector(pair.first, Vector3f(pair.second.y, -pair.second.x, pair.second.z), 0.1f, true); //dx, dy, 0.0f
        }
        if (_showNormal) {
          glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
          Axes::drawVector(pair.first, pair.second, 0.1f, true); //-dy, dx, 0.0f
        }
      }
    }
    glEnd();
  }
}

void Waves::drawWaves() const {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat pos[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  GLfloat lightColorDiffuse[] = {0.7f, 0.7f, 0.7f, 0.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);

  GLfloat specular[] = {0.7f, 0.7f, 0.9f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 80.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glColor4f(0.0f, 0.5f, 1.0f, 0.8f);
  for (auto row : _vertices) {
    glBegin(GL_TRIANGLE_STRIP);
    for (auto pair : row) {
      glNormal3f(pair.second.x, pair.second.y, pair.second.z);
      glVertex3f(pair.first.x, pair.first.y, pair.first.z);
    }
    glEnd();
  }

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void Waves::draw() const {
  drawWaves();
  drawDebug();
}

void Waves::toggleTangeants() {
  _showTangeant = !_showTangeant;
}

void Waves::toggleNormals() {
  _showNormal = !_showNormal;
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
