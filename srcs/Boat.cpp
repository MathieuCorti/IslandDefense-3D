//
//  Boat.cpp
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/7/18.
//

#include "includes/Boat.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "includes/Island.hpp"

Boat::Boat(const Color color, const Vector3f startPos) : Alive(BOATS_BASE_HEALTH), Movable(BOAT_SPEED, startPos) {
  Vertex::Ptr ttr = std::make_shared<Vertex>(Vector3f(0.05f, 0.025f, -0.025f));
  Vertex::Ptr ttl = std::make_shared<Vertex>(Vector3f(0.05f, 0.025f, 0.025f));
  Vertex::Ptr tbr = std::make_shared<Vertex>(Vector3f(-0.05f, 0.025f, -0.025f));
  Vertex::Ptr tbl = std::make_shared<Vertex>(Vector3f(-0.05f, 0.025f, 0.025f));
  Vertex::Ptr bbr = std::make_shared<Vertex>(Vector3f(0.0f, -0.025f, -0.025f));
  Vertex::Ptr bbl = std::make_shared<Vertex>(Vector3f(0.0f, -0.025f, 0.025f));

  Triangles triangles;
  Triangle(ttr, ttl, tbl).subdivide(2, triangles); // TOP
  Triangle(tbl, tbr, ttr).subdivide(2, triangles); // TOP
  Triangle(ttl, ttr, bbr).subdivide(2, triangles); // FRONT
  Triangle(bbr, bbl, ttl).subdivide(2, triangles); // FRONT
  Triangle(tbr, tbl, bbl).subdivide(2, triangles); // BACK
  Triangle(bbl, bbr, tbr).subdivide(2, triangles); // BACK
  Triangle(tbl, ttl, bbl).subdivide(2, triangles); // LEFT
  Triangle(ttr, tbr, bbr).subdivide(2, triangles); // RIGHT
  Shape shape = Shape(triangles, _coordinates, GL_TRIANGLES, color);
  shape.computePerVertexNormal();
  shape.generateBoundingBox();
  _shapes.emplace_back(shape);
  _cannon = std::make_shared<Cannon>(3.0f, 0.005f, color);
}

void Boat::draw() const {
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
  Displayable::draw();
  glPopMatrix();
  glDisable(GL_BLEND);

  if (Game::getInstance().getShowLight()) {
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }

  _cannon->draw();
}

void Boat::update() {
  _coordinates.y = Waves::computeHeight(_coordinates.x, _coordinates.z);
  float slope = Waves::computeSlope(_coordinates.x, _coordinates.z);
  _angle.z = static_cast<float>(std::atan(slope) * 180.0f / M_PI);
  _angle.x = -_angle.z;

  GLfloat rotation[16];
  (_angle * (M_PI / 180.0f)).toRotationMatrix(rotation);

  _cannon->setCoordinates(_coordinates + Vector3f{0.0f, 0.025f, 0.0f} * rotation);
  _cannon->setAngle(_angle);
  _cannon->update();
  computeAI();
}

void Boat::computeAI() {
  static auto island =  std::dynamic_pointer_cast<Island>(Game::getInstance().getEntities().at(ISLAND));
  
  _coordinates.x -= (_coordinates.x - island->getCoordinates().x) * _speed;
  _coordinates.z -= (_coordinates.z - island->getCoordinates().z) * _speed;
  
  // Auto destruction
  if (_coordinates.x < 0.2f && _coordinates.x > -0.2f 
    && _coordinates.z < 0.2f && _coordinates.z > -0.2f) {
    island->takeDamage(_currentHealth);
    _currentHealth = 0;
  }
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}

const std::list<Displayable *> &Boat::getCollidables() {
  _collidables.clear();
  for (auto e : _cannon->getCollidables()) {
    _collidables.push_back(e);
  }
  _collidables.push_back(this);
  return _collidables;
}