//
// Created by wilmot_g on 07/05/18.
//

#include "includes/Light.hpp"

Light::Light() : Displayable(Vector3f(-1.0f, 0.53f, -0.30f)) {}

void Light::draw() const {
  GLfloat pos[] = {_coordinates.x, _coordinates.y, _coordinates.z, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  GLfloat lightColorDiffuse[] = {0.7f, 0.7f, 0.7f, 0.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
}