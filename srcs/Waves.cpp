//
// Created by wilmot_g on 01/05/18.
//

#include "includes/Waves.hpp"
#include "includes/Game.hpp"

float Waves::_time = 0.0f;
float Waves::_maxHeight = 0.0f;

Waves::Waves() : _tess(64), _animate(true) {
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
  return a * kx * std::cos(kx * x + kz * z + shift);
}

float Waves::computeSlope(float x, float z) {
  return 0.5f * (sineNormal(x, z, (float) M_PI / 2.0f, 1.0f / 8.0f, 2.0f * (float) M_PI, 1.0f * (float) M_PI) +
                 sineNormal(x, z, (float) M_PI / 2.5f, 1.0f / 7.0f, 1.0f * (float) M_PI, 2.0f * (float) M_PI));
}

void Waves::update() {
  float xStep = 2.0f / _tess;
  float zStep = 2.0f / _tess;
  float xmax = 1.0;
  float zmax = 1.0;

  if (_animate) {
    _vertices.clear();
    float z;
    for (int i = 0; i <= _tess; ++i) {
      z = -zmax + i * zStep;
      std::vector<Vertex::Ptr> row;
      for (int j = 0; j <= _tess; j++) {
        float x = -xmax + j * xStep;
        float dx = 1.0f;
        float dy = computeSlope(x, z);
        float y = computeHeight(x, z);
        row.emplace_back(std::make_shared<Vertex>(Vector3f(x, y, z), Vector3f(-dy, dx, 0)));
        _maxHeight = std::max(_maxHeight, y);
      }
      _vertices.emplace_back(row);
    }

    _shapes.clear();
    for (int i = 0; i < _vertices.size() - 1; ++i) {
      const std::vector<Vertex::Ptr> &pointRow = _vertices[i];
      const std::vector<Vertex::Ptr> &pointUpRow = _vertices[i + 1];
      std::vector<Triangle> parts;
      for (int j = 0; j < pointRow.size() - 1; j++) {
        const Vertex::Ptr p1 = pointRow[j];
        const Vertex::Ptr p2 = pointRow[j + 1];
        const Vertex::Ptr p3 = pointUpRow[j];
        const Vertex::Ptr p4 = pointUpRow[j + 1];

        parts.emplace_back(p1, p2, p3);
        parts.emplace_back(p3, p2, p4);
      }
      _shapes.emplace_back(parts, GL_TRIANGLES, Color(0.0f, 0.5f, 1.0f, 0.8f));
    }
    _time += Game::getInstance().getDeltaTime();
  }
}

void Waves::draw() const {
  if (Game::getInstance().getShowLight()) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat specular[] = {0.7f, 0.7f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    GLfloat diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    GLfloat shininess = 80.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  }

  glEnable(GL_BLEND);
  Displayable::draw();
  if (Game::getInstance().getShowTangeant()) {
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    for (const Shape &row : _shapes) {
      for (const Triangle &t : row._parts) {
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        //Tangent
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        Axes::drawVector(t.v1->p, Vector3f(t.v1->n.y, -t.v1->n.x, t.v1->n.z), 0.1f, true);
        Axes::drawVector(t.v2->p, Vector3f(t.v2->n.y, -t.v2->n.x, t.v2->n.z), 0.1f, true);
        Axes::drawVector(t.v3->p, Vector3f(t.v3->n.y, -t.v3->n.x, t.v3->n.z), 0.1f, true);

        //Binormal (But really not)
        glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
        Axes::drawVector(t.v1->p, Vector3f(t.v1->n.z, -t.v1->n.x, t.v1->n.y), 0.1f, true);
        Axes::drawVector(t.v2->p, Vector3f(t.v2->n.z, -t.v2->n.x, t.v2->n.y), 0.1f, true);
        Axes::drawVector(t.v3->p, Vector3f(t.v3->n.z, -t.v3->n.x, t.v3->n.y), 0.1f, true);
      }
    }
    glEnd();
  }
  glDisable(GL_BLEND);

  if (Game::getInstance().getShowLight()) {
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
}

void Waves::toggleAnimation() {
  _animate = !_animate;
}

void Waves::doubleVertices() {
  Waves::_tess *= 2;
  _vertices.clear();
}

void Waves::halveSegments() {
  Waves::_tess /= 2;
  Waves::_tess = _tess < 4 ? 4 : _tess;
  _vertices.clear();
}
