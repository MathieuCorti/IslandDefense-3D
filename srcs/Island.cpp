//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(4.0f) {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  for (int i = 0; i < _tess; i++) {
    float z = -_zmax + i * zStep;
    std::vector<Vector3f> row;
    for (int j = 0; j < _tess; j++) {
      float x = -_xmax + j * xStep;
      row.emplace_back(x, islandPerlin(x, z), z);
    }
    _points.emplace_back(row);
  }

  for (int i = 0; i < _points.size() - 1; i++) {
    std::vector<Vector3f> &pointRow = _points[i];
    std::vector<Vector3f> &pointUpRow = _points[i + 1];
    std::vector<Triangle> newRow;
    for (int j = 0; j < pointRow.size() - 1; j++) {
      Vector3f &p1 = pointRow.at(j);
      Vector3f &p2 = pointRow.at(j + 1);
      Vector3f &p3 = pointUpRow.at(j);
      Vector3f &p4 = pointUpRow.at(j + 1);

      Vertex::Ptr v1, v2, v3, v4, v5;
      if (j == 0) {
        v1 = std::make_shared<Vertex>(Vertex(p1, p3, Vector3f()));
      } else {
        v1 = newRow[newRow.size() - 1].v2;
      }
      v2 = std::make_shared<Vertex>(Vertex(p3, p2, Vector3f()));
      if (i == 0) {
        v3 = std::make_shared<Vertex>(Vertex(p2, p1, Vector3f()));
      } else {
        v3 = _triangles[_triangles.size() - 1][j == 0 ? 1 : newRow.size() + 1].v3;
      }
      v4 = std::make_shared<Vertex>(Vertex(p2, p4, Vector3f()));
      v5 = std::make_shared<Vertex>(Vertex(p4, p3, Vector3f()));

      if (j == 0) {
        _vertices.emplace_back(v1);
      }
      _vertices.emplace_back(v2);
      if (i == 0) {
        _vertices.emplace_back(v3);
      }
      _vertices.emplace_back(v4);
      _vertices.emplace_back(v5);

      newRow.emplace_back(v1, v2, v3, computeNormal(v1->p1, v2->p1, v3->p1));
      newRow.emplace_back(v2, v4, v5, computeNormal(v5->p1, v4->p1, v2->p1));
    }
    _triangles.emplace_back(newRow);
  }

//  for (auto row : _triangles) {
//    for (auto t : row) {
//      glNormal3f(t.n.x, t.n.y, t.n.z);
//      glVertex3f(t.v1->p1.x, t.v1->p1.y, t.v1->p1.z);
//      glVertex3f(t.v2->p1.x, t.v2->p1.y, t.v2->p1.z);
//      glVertex3f(t.v3->p1.x, t.v3->p1.y, t.v3->p1.z);
//    }
//  }

//  float zs[2] = {-_zmax, _zmax};
//  for (int j = 0; j < _tess; j++) {
//    float x = -_xmax + j * xStep;
//    for (float z : zs) {
//      Vector3f p1 = Vector3f(x, -1, z);
//      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
//      Vector3f p3 = Vector3f(x + xStep, -1, z);
//      Vector3f p4 = Vector3f(x + xStep, islandPerlin(x + xStep, z), z);
//      _triangle.emplace_back(p1, p2, p3, computeNormal(p1, p2, p3));
//      _triangle.emplace_back(p3, p2, p4, computeNormal(p3, p2, p4));
//    }
//  }
//
//  float xs[2] = {-_xmax, _xmax};
//  for (int j = 0; j < _tess; j++) {
//    float z = -_zmax + j * zStep;
//    for (float x : xs) {
//      Vector3f p1 = Vector3f(x, -1, z);
//      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
//      Vector3f p3 = Vector3f(x, -1, z + zStep);
//      Vector3f p4 = Vector3f(x, islandPerlin(x, z + zStep), z + zStep);
//      _triangle.emplace_back(p1, p2, p3, computeNormal(p1, p2, p3));
//      _triangle.emplace_back(p3, p2, p4, computeNormal(p3, p2, p4));
//    }
//  }
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

  GLfloat specular[] = {0.0f, 0.0f, 0.0f, 0.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  GLfloat shininess = 128.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);
  for (auto row : _triangles) {
    for (auto t : row) {
      glNormal3f(t.n.x, t.n.y, t.n.z);
      glVertex3f(t.v1->p1.x, t.v1->p1.y, t.v1->p1.z);
      glVertex3f(t.v2->p1.x, t.v2->p1.y, t.v2->p1.z);
      glVertex3f(t.v3->p1.x, t.v3->p1.y, t.v3->p1.z);
    }
  }
  glEnd();

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  if (Game::getInstance().getShowNormal()) {
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    for (auto row : _triangles) {
      for (auto t : row) {
        Vector3f middle = {(t.v1->p1.x + t.v2->p1.x + t.v3->p1.x) / 3.0f,
                           (t.v1->p1.y + t.v2->p1.y + t.v3->p1.y) / 3.0f,
                           (t.v1->p1.z + t.v2->p1.z + t.v3->p1.z) / 3.0f};
        Axes::drawVector(middle, t.n, 0.1f, true);
      }
    }
    glEnd();
  }
}