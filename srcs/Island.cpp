//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "helpers/Axes.hpp"
#include "includes/Game.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(16.0f) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  for (int i = 0; i < _tess; i++) {
    std::vector<std::pair<Vector3f, Vector3f>> row;
    float z = -_zmax + i * zStep;
    for (int j = 0; j <= _tess; j++) {
      float x = -_xmax + j * xStep;
      float y = islandPerlin(x, z);
      float y2 = islandPerlin(x, z + zStep);
      row.emplace_back(Vector3f(x, y, z), computeNormalPerlin(j, i));
      row.emplace_back(Vector3f(x, y2, z + zStep), computeNormalPerlin(j, i + 1));
    }
    _vertices.push_back(row);
  }

  float z = -_zmax;
  std::vector<std::pair<Vector3f, Vector3f>> row;
  for (int j = 0; j <= _tess; j++) {
    float x = -_xmax + j * xStep;
    float y = islandPerlin(x, z);
    row.emplace_back(Vector3f(x, y, z), Vector3f(0, 0, z - 1));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(0, 0, z - 1));
  }
  _vertices.push_back(row);

  z = _zmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    float x = -_xmax + j * xStep;
    float y = islandPerlin(x, z);
    row.emplace_back(Vector3f(x, y, z), Vector3f(0, 0, z + 1));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(0, 0, z + 1));
  }
  _vertices.push_back(row);

  float x = -_xmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    z = -_zmax + j * zStep;
    float y = islandPerlin(x, z);
    row.emplace_back(Vector3f(x, y, z), Vector3f(x - 1, 0, 0));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(x - 1, 0, 0));
  }
  _vertices.push_back(row);

  x = _xmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    z = -_zmax + j * zStep;
    float y = islandPerlin(x, z);
    row.emplace_back(Vector3f(x, y, z), Vector3f(x + 1, 0, 0));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(x + 1, 0, 0));
  }
  _vertices.push_back(row);
}

Vector3f Island::computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
  Vector3f u = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
  Vector3f v = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
  Vector3f n = {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
  return n;
}

Vector3f Island::computeNormalPerlin(float i, float j) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  float z = -_zmax + i * zStep;
  float x = -_xmax + j * xStep;

  //  p2
  //p4p5p6
  //  p8
  Vector3f p2 = {x, islandPerlin(x, z + zStep), z + zStep};
  Vector3f p4 = {x - xStep, islandPerlin(x - xStep, z), z};
  Vector3f p5 = {x, islandPerlin(x, z), z};
  Vector3f p6 = {x + xStep, islandPerlin(x + xStep, z), z};
  Vector3f p8 = {x, islandPerlin(x, z - zStep), z - zStep};

  Vector3f n1 = computeNormal(p5, p4, p2);
  Vector3f n2 = computeNormal(p5, p2, p6);
  Vector3f n3 = computeNormal(p5, p6, p8);
  Vector3f n4 = computeNormal(p5, p8, p4);

  Vector3f n = {0.25f * (n1.x + n2.x + n3.x + n4.x),
                0.25f * (n1.y + n2.y + n3.y + n4.y),
                0.25f * (n1.z + n2.z + n3.z + n4.z)
  };

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
  for (auto row : _vertices) {
    glBegin(GL_QUAD_STRIP);
    for (auto pair : row) {
      glNormal3f(pair.second.x, pair.second.y, pair.second.z);
      glVertex3f(pair.first.x, pair.first.y, pair.first.z);
    }
    glEnd();
  }

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  if (Game::getInstance().getShowNormal()) {
    glBegin(GL_LINES);
    for (auto row : _vertices) {
      for (auto pair : row) {
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        Axes::drawVector(pair.first, Vector3f(pair.second.x, pair.second.y, pair.second.z), 0.1f, true);
      }
    }
    glEnd();
  }
}