//
//  Boat.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/7/18.
//

#include "includes/Boat.hpp"
#include "includes/Waves.hpp"

Boat::Boat(const Color color) : Movable(0.05f, Vector3f(-0.3f, 0.0f, 0.0f)) {
  Vertex::Ptr ttr = std::make_shared<Vertex>(Vector3f(0.1f, 0.05f, -0.05f));
  Vertex::Ptr ttl = std::make_shared<Vertex>(Vector3f(0.1f, 0.05f, 0.05f));
  Vertex::Ptr tbr = std::make_shared<Vertex>(Vector3f(-0.1f, 0.05f, -0.05f));
  Vertex::Ptr tbl = std::make_shared<Vertex>(Vector3f(-0.1f, 0.05f, 0.05f));
  Vertex::Ptr bbr = std::make_shared<Vertex>(Vector3f(0.0f, -0.05f, -0.05f));
  Vertex::Ptr bbl = std::make_shared<Vertex>(Vector3f(0.0f, -0.05f, 0.05f));

  Shape shape = Shape({Triangle(ttr, ttl, tbl).computeNormal(), // TOP
                       Triangle(tbl, tbr, ttr).computeNormal(), // TOP
                       Triangle(ttl, ttr, bbr).computeNormal(), // FRONT
                       Triangle(bbr, bbl, ttl).computeNormal(), // FRONT
                       Triangle(tbl, tbr, bbr).computeNormal(), // BACK
                       Triangle(bbr, bbl, tbl).computeNormal(), // BACK
                       Triangle(ttl, tbl, bbl).computeNormal(), // LEFT
                       Triangle(ttr, tbr, bbr).computeNormal()  // RIGHT
                      }, GL_POLYGON, color);
  shape.computePerVertexNormal();

  _shapes.push_back(shape);
  _cannon = std::make_shared<Cannon>(0, 3.0f, color);
}

void Boat::draw() const {
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
  GLfloat shininess = 64.0f;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glPushMatrix();
  glTranslatef(_coordinates.x, _coordinates.y, _coordinates.z);
  glRotatef(_angle.x, 1.0, 0.0, 0.0);
  glRotatef(_angle.y, 0.0, 1.0, 0.0);
  glRotatef(_angle.z, 0.0, 0.0, 1.0);
  Displayable::draw();
  _cannon->draw();
  glPopMatrix();

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_BLEND);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void Boat::update() {
  _coordinates.y = Waves::computeHeight(_coordinates.x, _coordinates.z);
  float slope = Waves::computeSlope(_coordinates.x, _coordinates.z);
  _angle.z = static_cast<float>(std::atan(slope) * 180.0f / M_PI);
  _angle.x = -_angle.z;
  _cannon->update();
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}