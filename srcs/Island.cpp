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
  computePerVertexNormal();
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
    std::vector<Triangle::Ptr> newRow;
    for (int j = 0; j < pointRow.size() - 1; j++) {
      const Vertex::Ptr p1 = pointRow.at(j);
      const Vertex::Ptr p2 = pointRow.at(j + 1);
      const Vertex::Ptr p3 = pointUpRow.at(j);
      const Vertex::Ptr p4 = pointUpRow.at(j + 1);

      newRow.emplace_back(std::make_shared<Triangle>(p1, p2, p3, computeNormal(p3->p, p2->p, p1->p)));
      newRow.emplace_back(std::make_shared<Triangle>(p3, p2, p4, computeNormal(p4->p, p2->p, p3->p)));
    }
    _triangles.emplace_back(newRow);
  }
}

void Island::computePerVertexNormal() {
  for (auto &row : _triangles) {
    for (auto &t : row) {
      t->v1->n.x += t->n.x;
      t->v1->n.y += t->n.y;
      t->v1->n.z += t->n.z;
      t->v2->n.x += t->n.x;
      t->v2->n.y += t->n.y;
      t->v2->n.z += t->n.z;
      t->v3->n.x += t->n.x;
      t->v3->n.y += t->n.y;
      t->v3->n.z += t->n.z;
    }
  }
  for (auto &row : _triangles) {
    for (auto &t : row) {
      t->v1->n.normalize();
      t->v2->n.normalize();
      t->v3->n.normalize();
    }
  }
}

Vector3f Island::computeNormal(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
  Vector3f u = {p2.x - p1.x,
                p2.y - p1.y,
                p2.z - p1.z};
  Vector3f v = {p3.x - p1.x,
                p3.y - p1.y,
                p3.z - p1.z};
  Vector3f n = {u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x};
  return n.normalize();
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
  glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  for (auto &row : _triangles) {
    for (auto &t : row) {
      glNormal3f(t->v1->n.x, t->v1->n.y, t->v1->n.z);
      glVertex3f(t->v1->p.x, t->v1->p.y, t->v1->p.z);
      glNormal3f(t->v2->n.x, t->v2->n.y, t->v2->n.z);
      glVertex3f(t->v2->p.x, t->v2->p.y, t->v2->p.z);
      glNormal3f(t->v3->n.x, t->v3->n.y, t->v3->n.z);
      glVertex3f(t->v3->p.x, t->v3->p.y, t->v3->p.z);
    }
  }
  glEnd();
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  if (Game::getInstance().getShowNormal()) {
    glBegin(GL_LINES);
    for (auto &row : _triangles) {
      for (auto &t : row) {
        Axes::drawVector(t->v1->p, t->v1->n, 0.1f, true);
        Axes::drawVector(t->v2->p, t->v2->n, 0.1f, true);
        Axes::drawVector(t->v3->p, t->v3->n, 0.1f, true);
      }
    }
    glEnd();
  }
}