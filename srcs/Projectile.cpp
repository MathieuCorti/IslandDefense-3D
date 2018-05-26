//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

#define PROJECTILE_DAMAGES 1

Projectile::Projectile(float t, Vector3f coordinates, Vector3f velocity, Color c) : Displayable(coordinates),
                                                                                    Alive(1),
                                                                                    _color(c),
                                                                                    _startT(t),
                                                                                    _start(coordinates),
                                                                                    _velocity(velocity) {}

Shape Projectile::getCircle(float radius, Vector3f center) {
//  Shape shape;
//  Vector3f coordinates;
//
//  shape._mode = GL_LINE_STRIP;
//  coordinates.x = static_cast<float>(radius * std::cos(359 * M_PI / 180.0f));
//  coordinates.y = static_cast<float>(radius * std::sin(359 * M_PI / 180.0f));
//  coordinates.z = 0;
//  shape._parts.emplace_back(center.x + coordinates.x, center.y + coordinates.y, center.z + coordinates.z);
//  for (int j = 0; j < 360; j++) {
//    coordinates.x = static_cast<float>(radius * std::cos(j * M_PI / 180.0f));
//    coordinates.y = static_cast<float>(radius * std::sin(j * M_PI / 180.0f));
//    shape._parts.emplace_back(center.x + coordinates.x, center.y + coordinates.y, center.z + coordinates.z);
//  }
//  return shape;
  return Shape({});
}

void Projectile::update() {
  if (getCurrentHealth() == 0) {
    return;
  }

  float t = Game::getInstance().getTime() - _startT;
  _coordinates.x = _start.x + _velocity.x * t;
  _coordinates.y = _start.y + _velocity.y * t + g * t * t / 2.0f;
  _coordinates.z = _start.z + _velocity.z * t;
  float wave = Waves::computeHeight(_coordinates.x, _coordinates.z);

  //TODO : collisions

  if (_coordinates.y < wave || _coordinates.y > 1 ||
      _coordinates.x < -1 || _coordinates.x > 1 ||
      _coordinates.z < -1 || _coordinates.z > 1) {
    _currentHealth = 0;
  }
}

void Projectile::draw() const {
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
  glTranslatef(_coordinates.x, _coordinates.y, _coordinates.z);
  //TODO : get circle
  glColor4f(_color.r, _color.g, _color.b, _color.a);
  glutSolidSphere(0.01f * 2.0f, 20, 20);
  glPopMatrix();
  glDisable(GL_BLEND);

  if (Game::getInstance().getShowLight()) {
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
}