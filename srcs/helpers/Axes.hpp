//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include <cmath>
#include "Glut.hpp"
#include "Displayable.hpp"
#include "../includes/Waves.hpp"

class Axes : public Displayable {
public:

  //TYPEDEF
  typedef struct {
    float x, y;
  } Vec2f;

  static void drawVector(float x, float y, float a, float b, float s, bool normalize, float red, float green,
                         float blue) {
    float magnitude = std::sqrt(a * a + b * b);
    a = (normalize ? a / magnitude : a) * s;
    b = (normalize ? b / magnitude : b) * s;

    glColor3f(red, green, blue);
    glVertex3f(x, y, 0);
    glVertex3f(x + a, y + b, 0);
  }

  void draw() const override {
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -1);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
  }
};