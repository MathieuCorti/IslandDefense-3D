//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "helpers/Axes.hpp"
#include "includes/Game.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(128.0f) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  for (int i = 0; i < _tess; i++) {
    float z = -_zmax + i * zStep;
    for (int j = 0; j < _tess; j++) {
      float x = -_xmax + j * xStep;
      Vector3f p1 = Vector3f(x, islandPerlin(x, z), z);
      Vector3f p2 = Vector3f(x, islandPerlin(x, z + zStep), z + zStep);
      Vector3f p3 = Vector3f(x + xStep, islandPerlin(x + xStep, z), z);
      Vector3f p4 = Vector3f(x + xStep, islandPerlin(x + xStep, z + zStep), z + zStep);
      _triangle.emplace_back(p1, p2, p3, computeNormal(p1, p2, p3));
      _triangle.emplace_back(p3, p2, p4, computeNormal(p3, p2, p4));
    }
  }

  float zs[2] = {-_zmax, _zmax};
  for (int j = 0; j < _tess; j++) {
    float x = -_xmax + j * xStep;
    for (float z : zs) {
      Vector3f p1 = Vector3f(x, -1, z);
      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
      Vector3f p3 = Vector3f(x + xStep, -1, z);
      Vector3f p4 = Vector3f(x + xStep, islandPerlin(x + xStep, z), z);
      _triangle.emplace_back(p1, p2, p3, computeNormal(p1, p2, p3));
      _triangle.emplace_back(p3, p2, p4, computeNormal(p3, p2, p4));
    }
  }

  float xs[2] = {-_xmax, _xmax};
  for (int j = 0; j < _tess; j++) {
    float z = -_zmax + j * zStep;
    for (float x : xs) {
      Vector3f p1 = Vector3f(x, -1, z);
      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
      Vector3f p3 = Vector3f(x, -1, z + zStep);
      Vector3f p4 = Vector3f(x, islandPerlin(x, z + zStep), z + zStep);
      _triangle.emplace_back(p1, p2, p3, computeNormal(p1, p2, p3));
      _triangle.emplace_back(p3, p2, p4, computeNormal(p3, p2, p4));
    }
  }
}

Vector3f Island::computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
  Vector3f u = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
  Vector3f v = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
  Vector3f n = {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
  return n.normalize();
}

float Island::islandPerlin(float x, float z) const {
  return Waves::maxHeight() +
         perlin2d(std::max(0.0f, _xmax + x) * 500.0f, std::max(0.0f, _zmax + z) * 500.0f, 0.03f, 8) * 0.2f;
}

void Island::draw() const {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat specular[] = {0.0f, 0.0f, 0.0f, 0.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 128.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (auto t : _triangle) {
    glNormal3f(t.n.x, t.n.y, t.n.z);
    glVertex3f(t.p1.x, t.p1.y, t.p1.z);
    glVertex3f(t.p2.x, t.p2.y, t.p2.z);
    glVertex3f(t.p3.x, t.p3.y, t.p3.z);
  }
  glEnd();

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  if (Game::getInstance().getShowNormal()) {
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    for (auto t : _triangle) {
      Vector3f middle = {(t.p1.x + t.p2.x + t.p3.x) / 3.0f,
                         (t.p1.y + t.p2.y + t.p3.y) / 3.0f,
                         (t.p1.z + t.p2.z + t.p3.z) / 3.0f};
      Axes::drawVector(middle, t.n, 0.1f, true);
    }
    glEnd();
  }
}