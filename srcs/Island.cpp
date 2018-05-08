//
// Created by wilmot_g on 03/05/18.
//

#include "includes/Island.hpp"
#include "helpers/Perlin.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

Island::Island() : _xmax(0.1), _zmax(0.1), _tess(5.0f) {
  generateTopTriangles();
//  generateBottomTriangles();
  computePerVertexNormal();
}

void Island::generateTopTriangles() {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  PointMap top;
  for (int i = 0; i <= _tess; i++) {
    float z = -_zmax + i * zStep;
    std::vector<Vector3f> rowTop;
    for (int j = 0; j <= _tess; j++) {
      float x = -_xmax + j * xStep;
      rowTop.emplace_back(x, islandPerlin(x, z), z);
    }
    top.emplace_back(rowTop);
  }

  for (int i = 0; i < top.size() - 1; i++) {
    const std::vector<Vector3f> &pointRow = top[i];
    const std::vector<Vector3f> &pointUpRow = top[i + 1];
    std::vector<Triangle> newRow;
    for (int j = 0; j < pointRow.size() - 1; j++) {
      const Vector3f &p1 = pointRow.at(j);
      const Vector3f &p2 = pointRow.at(j + 1);
      const Vector3f &p3 = pointUpRow.at(j);
      const Vector3f &p4 = pointUpRow.at(j + 1);

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

      newRow.emplace_back(v1, v2, v3, computeNormal(v1->p, v2->p, v3->p));
      newRow.emplace_back(v2, v4, v5, computeNormal(v2->p, v4->p, v5->p).invert());
    }
    _triangles.emplace_back(newRow);
  }
}

void Island::generateBottomTriangles() {
  float xStep = 2 * _xmax / _tess;
  float zStep = 2 * _zmax / _tess;

  float zs[2] = {-_zmax, _zmax};
  for (int j = 0; j < _tess; j++) {
    float x = -_xmax + j * xStep;
    std::vector<Triangle> newRow;
    for (float z : zs) {
      Vector3f p1 = Vector3f(x, -1, z);
      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
      Vector3f p3 = Vector3f(x + xStep, -1, z);
      Vector3f p4 = Vector3f(x + xStep, islandPerlin(x + xStep, z), z);
      Vertex::Ptr v1 = std::make_shared<Vertex>(p1, p2, Vector3f());
      Vertex::Ptr v2 = std::make_shared<Vertex>(p2, p3, Vector3f());
      Vertex::Ptr v3 = std::make_shared<Vertex>(p3, p4, Vector3f());
      Vertex::Ptr v4 = std::make_shared<Vertex>(p4, p1, Vector3f());
      Vector3f n1 = computeNormal(v1->p, v2->p, v3->p);
      Vector3f n2 = computeNormal(v3->p, v2->p, v4->p);
      newRow.emplace_back(v1, v2, v3, z == _zmax ? n1.invert() : n1);
      newRow.emplace_back(v3, v2, v4, z == _zmax ? n2.invert() : n2);
    }
    _triangles.emplace_back(newRow);
  }

  float xs[2] = {-_xmax, _xmax};
  for (int j = 0; j < _tess; j++) {
    float z = -_zmax + j * zStep;
    std::vector<Triangle> newRow;
    for (float x : xs) {
      Vector3f p1 = Vector3f(x, -1, z);
      Vector3f p2 = Vector3f(x, islandPerlin(x, z), z);
      Vector3f p3 = Vector3f(x, -1, z + zStep);
      Vector3f p4 = Vector3f(x, islandPerlin(x, z + zStep), z + zStep);
      Vertex::Ptr v1 = std::make_shared<Vertex>(p1, p2, Vector3f());
      Vertex::Ptr v2 = std::make_shared<Vertex>(p2, p3, Vector3f());
      Vertex::Ptr v3 = std::make_shared<Vertex>(p3, p4, Vector3f());
      Vertex::Ptr v4 = std::make_shared<Vertex>(p4, p1, Vector3f());
      Vector3f n1 = computeNormal(v1->p, v2->p, v3->p);
      Vector3f n2 = computeNormal(v3->p, v2->p, v4->p);
      newRow.emplace_back(v1, v2, v3, x == -_xmax ? n1.invert() : n1);
      newRow.emplace_back(v3, v2, v4, x == -_xmax ? n2.invert() : n2);
    }
    _triangles.emplace_back(newRow);
  }
}

void Island::computePerVertexNormal() {
  for (auto row : _triangles) {
    for (auto t : row) {
      t.v1->n.x += t.n.x;
      t.v1->n.y += t.n.y;
      t.v1->n.z += t.n.z;
      t.v2->n.x += t.n.x;
      t.v2->n.y += t.n.y;
      t.v2->n.z += t.n.z;
      t.v3->n.x += t.n.x;
      t.v3->n.y += t.n.y;
      t.v3->n.z += t.n.z;
    }
  }
  for (auto row : _triangles) {
    for (auto t : row) {
      t.v1->n.normalize();
      t.v2->n.normalize();
      t.v3->n.normalize();
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
//  glEnable(GL_NORMALIZE);
//  glEnable(GL_RESCALE_NORMAL);

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
      glNormal3f(t.v1->n.x, t.v1->n.y, t.v1->n.z);
      std::cout << t.v1->n << std::endl;
      glVertex3f(t.v1->p.x, t.v1->p.y, t.v1->p.z);
      std::cout << t.v1->p << std::endl;
      glNormal3f(t.v2->n.x, t.v2->n.y, t.v2->n.z);
      std::cout << t.v2->n << std::endl;
      glVertex3f(t.v2->p.x, t.v2->p.y, t.v2->p.z);
      std::cout << t.v2->p << std::endl;
      glNormal3f(t.v3->n.x, t.v3->n.y, t.v3->n.z);
      std::cout << t.v3->n << std::endl;
      glVertex3f(t.v3->p.x, t.v3->p.y, t.v3->p.z);
      std::cout << t.v3->p << std::endl;
      std::cout << "-------------" << std::endl;
    }
  }
  glEnd();
  
//  glDisable(GL_RESCALE_NORMAL);
//  glDisable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  if (Game::getInstance().getShowNormal()) {
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    for (auto &row : _triangles) {
      for (auto &t : row) {
        Axes::drawVector({(t.v1->p.x + t.v1->p2.x) / 2, (t.v1->p.y + t.v1->p2.y) / 2, (t.v1->p.z + t.v1->p2.z) / 2},
                         t.v1->n, 0.1f, true);
        Axes::drawVector({(t.v2->p.x + t.v2->p2.x) / 2, (t.v2->p.y + t.v2->p2.y) / 2, (t.v2->p.z + t.v2->p2.z) / 2},
                         t.v2->n, 0.1f, true);
        Axes::drawVector({(t.v3->p.x + t.v3->p2.x) / 2, (t.v3->p.y + t.v3->p2.y) / 2, (t.v3->p.z + t.v3->p2.z) / 2},
                         t.v3->n, 0.1f, true);
      }
    }
    glEnd();
  }
}