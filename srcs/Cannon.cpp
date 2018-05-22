//
// Created by wilmot_g on 24/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Cannon.hpp"
#include "includes/Game.hpp"

const float g = -9.8f;

Cannon::Cannon(float rotation, float speed, float radius, Color color) : _color(color),
                                                           _rotation(rotation),
                                                           _speed(speed),
                                                           _radius(radius),
                                                           _lastFire(-1.0f),
                                                           _lastDefence(-5.0f) {
  Vertices vertices;

  std::vector<Vertex::Ptr> top;
  std::vector<Vertex::Ptr> bottom;
  Vector3f p;
  for (int j = 0; j < 45; j++) {
    p.x = static_cast<float>(radius * std::cos(j * 8 * M_PI / 180.0f));
    p.y = 0.0f;
    p.z = static_cast<float>(radius * std::sin(j * 8 * M_PI / 180.0f));
    bottom.push_back(std::make_shared<Vertex>(p));
    p.y = 0.1f;
    top.push_back(std::make_shared<Vertex>(p));
  }
  vertices.push_back(bottom);
  vertices.push_back(top);

  Triangles triangles;
  Vertex::Ptr centerBottom = std::make_shared<Vertex>(Vector3f(0.0f, 0.0f, 0.0f));
  Vertex::Ptr centerTop = std::make_shared<Vertex>(Vector3f(0.0f, 0.1f, 0.0f));
  Vertex::Ptr bl = vertices[0][vertices[0].size() - 1];
  Vertex::Ptr br = vertices[0][0];
  Vertex::Ptr tl = vertices[1][vertices[1].size() - 1];
  Vertex::Ptr tr = vertices[1][0];
  triangles.emplace_back(bl, tl, tr, Triangle::computeNormal(bl->p, tl->p, tr->p).invert());
  triangles.emplace_back(tr, br, bl, Triangle::computeNormal(tr->p, br->p, bl->p).invert());
  triangles.emplace_back(br, centerBottom, bl, Triangle::computeNormal(br->p, centerBottom->p, bl->p));
  triangles.emplace_back(tr, centerTop, tl, Triangle::computeNormal(tr->p, centerTop->p, tl->p));
  for (int i = 0; i < vertices[0].size() - 1; i++) {
    bl = vertices[0][i];
    br = vertices[0][i + 1];
    tl = vertices[1][i];
    tr = vertices[1][i + 1];
    triangles.emplace_back(bl, tl, tr, Triangle::computeNormal(bl->p, tl->p, tr->p).invert());
    triangles.emplace_back(tr, br, bl, Triangle::computeNormal(tr->p, br->p, bl->p).invert());
    triangles.emplace_back(br, centerBottom, bl, Triangle::computeNormal(br->p, centerBottom->p, bl->p));
    triangles.emplace_back(tr, centerTop, tl, Triangle::computeNormal(tr->p, centerTop->p, tl->p));
  }
  Shape shape = Shape(triangles, GL_TRIANGLES, color);
  shape.computePerVertexNormal();
  _shapes.push_back(shape);
}

void Cannon::drawDirection() const {
//  glPushMatrix();
//  glTranslatef(_coordinates.x, _coordinates.y, _coordinates.z);
//  glRotatef(static_cast<GLfloat>(_angle + _rotation * 180 / M_PI - 90), 0.0, 0.0, 1.0);
//  glPopMatrix();
}

void Cannon::drawTrajectory() const {
  glBegin(GL_LINE_STRIP);

  float t = 0;
  for (;;) {
    float x = _coordinates.x + _velocity.x * t + _velocity.x / 20 * _scale;
    float y = _coordinates.y + _velocity.y * t + g * t * t / 2.0f + _velocity.y / 20 * _scale;

    if (y < -1 || x > 1 || x < -1) {
      break;
    }

    glVertex2f(x, y);
    t += 0.01;
  }
  glEnd();
}

Projectile::Ptr Cannon::blast() {
  if (Game::getInstance().getTime() - _lastFire > 1.0f) {
    _lastFire = Game::getInstance().getTime();
    return std::make_shared<Projectile>(Game::getInstance().getTime(), _coordinates, _velocity, _color);
  }
  return nullptr;
}

Pellet::Ptr Cannon::defend() {
  if (Game::getInstance().getTime() - _lastDefence > 5.0f) {
    _lastDefence = Game::getInstance().getTime();
    return std::make_shared<Pellet>(Game::getInstance().getTime(), _coordinates, this, _color);
  }
  return nullptr;
}

void Cannon::draw() const {
  glPushMatrix();
  glTranslatef(_coordinates.x, _coordinates.y, _coordinates.z);
  glRotatef(_angle.x, 1.0, 0.0, 0.0);
  glRotatef(_angle.y, 0.0, 1.0, 0.0);
  glRotatef(_angle.z, 0.0, 0.0, 1.0);
  Displayable::draw();
  glPopMatrix();
}

void Cannon::speed(float value) {
  _speed += value;
  _speed = _speed < 0 ? 0 : _speed;
}

void Cannon::rotation(float angle) {
  _rotation += angle;
  _rotation = static_cast<float>(_rotation < (_inverted ? -2 * M_PI : 0) ? (_inverted ? -2 * M_PI : 0) : _rotation);
  _rotation = static_cast<float>(_rotation > (_inverted ? -M_PI : M_PI) ? (_inverted ? -M_PI : M_PI) : _rotation);
}

void Cannon::setPos(float x, float y, float angle) {
//  _coordinates.x = x;
//  _coordinates.y = y;
//  _angle = angle + (_inverted ? 0 : 180);
//  _velocity.x = static_cast<float>(std::cos(_rotation + _angle * M_PI / 180.0f) * _speed);
//  _velocity.y = static_cast<float>(std::sin(_rotation + _angle * M_PI / 180.0f) * _speed);
}

const Vector3f &Cannon::getVelocity() const {
  return _velocity;
}

float Cannon::getScale() const {
  return _scale;
}
