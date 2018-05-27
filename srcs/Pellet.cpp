//
// Created by wilmot_g on 01/04/18.
//

#include "includes/Pellet.hpp"
#include "includes/Game.hpp"

Pellet::Pellet(float t, Vector3f coordinates, Vector3f angle, float rotation, Color c) : Displayable(coordinates),
                                                                                         Alive(1),
                                                                                         _color(c),
                                                                                         _startT(t),
                                                                                         _radius(0) {
  _rotation = rotation;
  _angle = angle;
  _collidables.push_back(this);
  update();
}

void Pellet::updateShape() {
  Vertices vertices;

  std::vector<Vertex::Ptr> bottom;
  Vector3f p;
  for (int j = 0; j < 20; j++) {
    p.y = static_cast<float>(_radius * std::cos(j * (360.0f / 20.0f) * M_PI / 180.0f));
    p.x = 0.0f;
    p.z = static_cast<float>(_radius * std::sin(j * (360.0f / 20.0f) * M_PI / 180.0f));
    bottom.push_back(std::make_shared<Vertex>(p));
  }
  vertices.push_back(bottom);

  Triangles triangles;
  Vertex::Ptr centerBottom = std::make_shared<Vertex>(Vector3f(0.0f, 0.0f, 0.0f));
  Vertex::Ptr bl = vertices[0][vertices[0].size() - 1];
  Vertex::Ptr br = vertices[0][0];
  triangles.emplace_back(bl, centerBottom, br, Triangle::computeNormal(bl->p, centerBottom->p, br->p));
  for (int i = 0; i < vertices[0].size() - 1; i++) {
    bl = vertices[0][i];
    br = vertices[0][i + 1];
    triangles.emplace_back(bl, centerBottom, br, Triangle::computeNormal(bl->p, centerBottom->p, br->p));
  }
  Shape shape = Shape(triangles, _coordinates, GL_TRIANGLES, _color);
  shape.computePerVertexNormal();
  shape.generateBoundingBox();
  _shapes.clear();
  _shapes.emplace_back(shape);
}

void Pellet::update() {
  if (getCurrentHealth() == 0) {
    return;
  }
  float x = Game::getInstance().getTime() - _startT;
  if (x) {
    _radius += x / 100.0f;
    updateShape();
  }
  if (_radius > 0.1f) {
    _currentHealth = 0;
  }
}

void Pellet::draw() const {
  if (Game::getInstance().getShowLight()) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    GLfloat specular[] = {1.0f, 0.3f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    GLfloat shininess = 64.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  }

  glEnable(GL_BLEND);
  glPushMatrix();
  GLfloat m[16];
  glMultMatrixf(_coordinates.toTranslationMatrix(m));
  glMultMatrixf((_angle * (M_PI / 180.0f)).toRotationMatrix(m));
  glMultMatrixf((Vector3f{0.0f, 0.0f, _rotation} * (M_PI / 180.0f)).toRotationMatrix(m));
  Displayable::draw();
  glPopMatrix();
  glDisable(GL_BLEND);

  if (Game::getInstance().getShowLight()) {
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
}
