//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(64.0f) {
  generateTopTriangles();
  for (Shape &shape : _shapes) {
    shape.computePerVertexNormal();
  }
}

void Island::generateTopTriangles() {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  float z;
  for (int i = 0; i <= _tess; i++) {
    if (i == 0) {
      z = -_zmax;
      std::vector<Vertex::Ptr> row1;
      for (int j = 0; j <= _tess; j++) {
        float x = -_xmax + j * xStep;
        if (j == 0) {
          row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        }
        row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        if (j == _tess) {
          row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        }
      }
      _vertices.emplace_back(row1);
    }
    z = -_zmax + i * zStep;
    std::vector<Vertex::Ptr> row;
    for (int j = 0; j <= _tess; j++) {
      float x = -_xmax + j * xStep;
      if (j == 0) {
        row.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
      }
      row.emplace_back(std::make_shared<Vertex>(Vector3f(x, islandPerlin(x, z), z)));
      if (j == _tess) {
        row.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
      }
    }
    _vertices.emplace_back(row);
    if (i == _tess) {
      z = _zmax;
      std::vector<Vertex::Ptr> row1;
      for (int j = 0; j <= _tess; j++) {
        float x = -_xmax + j * xStep;
        if (j == 0) {
          row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        }
        row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        if (j == _tess) {
          row1.emplace_back(std::make_shared<Vertex>(Vector3f(x * 3.0f, -0.8f, z * 3.0f)));
        }
      }
      _vertices.emplace_back(row1);
    }
  }

  for (int i = 0; i < _vertices.size() - 1; i++) {
    const std::vector<Vertex::Ptr> &pointRow = _vertices[i];
    const std::vector<Vertex::Ptr> &pointUpRow = _vertices[i + 1];
    std::vector<Triangle> parts;
    for (int j = 0; j < pointRow.size() - 1; j++) {
      const Vertex::Ptr p1 = pointRow.at(j);
      const Vertex::Ptr p2 = pointRow.at(j + 1);
      const Vertex::Ptr p3 = pointUpRow.at(j);
      const Vertex::Ptr p4 = pointUpRow.at(j + 1);

      parts.emplace_back(p1, p2, p3, Triangle::computeNormal(p1->p, p2->p, p3->p));
      parts.emplace_back(p3, p2, p4, Triangle::computeNormal(p3->p, p2->p, p4->p));
    }
    _shapes.emplace_back(parts, GL_TRIANGLES, Color(1.0f, 0.5f, 0.0f, 1.0f));
  }
}

float Island::islandPerlin(float x, float z) const {
  return Waves::maxHeight() +
         perlin2d(std::max(0.0f, _xmax + x) * 500.0f, std::max(0.0f, _zmax + z) * 500.0f, 0.03f, 8) * 0.1f;
}

void Island::draw() const {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat specular[] = {0.1f, 0.1f, 0.1f, 0.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 128.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glShadeModel(GL_SMOOTH);
  Displayable::draw();

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}