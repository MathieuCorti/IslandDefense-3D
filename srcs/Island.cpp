//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "helpers/Axes.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(64.0f) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  for (int i = 0; i < _tess; i++) {
    std::vector<std::pair<Vector3f, Vector3f>> row;
    float z = -_zmax + i * zStep;
    for (int j = 0; j <= _tess; j++) {
      float x = -_xmax + j * xStep;
      float y = islandPerlin(j, i);
      float y2 = islandPerlin(j, i + 1);
      row.emplace_back(Vector3f(x, y, z), perlinNormal(j, i));
      row.emplace_back(Vector3f(x, y2, z + zStep), perlinNormal(j, i + 1));
    }
    _vertices.push_back(row);
  }

  float z = -_zmax;

  std::vector<std::pair<Vector3f, Vector3f>> row;
  for (int j = 0; j <= _tess; j++) {
    float x = -_xmax + j * xStep;
    float y = islandPerlin(j, 0);
    row.emplace_back(Vector3f(x, y, z), Vector3f(0, 0, z - 1));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(0, 0, z - 1));
  }
  _vertices.push_back(row);
  z = _zmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    float x = -_xmax + j * xStep;
    float y = islandPerlin(j, _tess - 1);
    row.emplace_back(Vector3f(x, y, z), Vector3f(0, 0, z + 1));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(0, 0, z + 1));
  }
  _vertices.push_back(row);
  float x = -_xmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    z = -_zmax + j * zStep;
    float y = islandPerlin(0, j);
    row.emplace_back(Vector3f(x, y, z), Vector3f(x - 1, 0, 0));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(x - 1, 0, 0));
  }
  _vertices.push_back(row);
  x = _xmax;
  row.clear();
  for (int j = 0; j <= _tess; j++) {
    z = -_zmax + j * zStep;
    float y = islandPerlin(_tess - 1, j);
    row.emplace_back(Vector3f(x, y, z), Vector3f(x + 1, 0, 0));
    row.emplace_back(Vector3f(x, -1, z), Vector3f(x + 1, 0, 0));
  }
  _vertices.push_back(row);
}

Vector3f Island::perlinNormal(float i, float j) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  float z = -_zmax + i * zStep;
  float x = -_xmax + j * xStep;

  Vector3f p1 = {x, islandPerlin(j, i), z};
  Vector3f p2 = {x, islandPerlin(j, i + 1), z + zStep};
  Vector3f p3 = {x + xStep, islandPerlin(j + 1, i), z};

  std::cout << "p1: " << p1 << std::endl;
  std::cout << "p2: " << p2 << std::endl;
  std::cout << "p3: " << p3 << std::endl;

  Vector3f u = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
  Vector3f v = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};

  std::cout << "u: " << u << std::endl;
  std::cout << "v: " << v << std::endl;

  Vector3f n = {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
  std::cout << "n: " << n << std::endl;
  Axes::normalize(n);
  std::cout << "n: " << n << std::endl;
  return n;
}

float Island::islandPerlin(float x, float z) const {
  return Waves::maxHeight() + perlin2d(x, z, 0.03f, 8) * 0.1f;
}

void Island::draw() const {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat pos[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  GLfloat lightColorDiffuse[] = {0.7f, 0.7f, 0.7f, 0.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);

  GLfloat specular[] = {0.1f, 0.1f, 0.1f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 128.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


  glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
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
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

//  glBegin(GL_LINES);
//  for (auto row : _vertices) {
//    for (auto pair : row) {
//      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//      Axes::drawVector(pair.first, Vector3f(pair.second.x, pair.second.y, pair.second.z), 0.1f, true);
//    }
//  }
//  glEnd();
}