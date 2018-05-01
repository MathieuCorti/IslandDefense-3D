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
  static void drawVector(Vector3f a, Vector3f b, float s, bool normalize) {
    float magnitude = std::sqrt(b.x * b.x + b.y * b.y);
    b.x = (normalize ? b.x / magnitude : b.x) * s;
    b.y = (normalize ? b.y / magnitude : b.y) * s;
    b.z = (normalize ? b.z / magnitude : b.z) * s;

    glVertex3f(a.x, a.y, a.z);
    glVertex3f(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  void draw() const override {
    glBegin(GL_LINES);
    //X R
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    //Y G
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    //Z B
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -1);
    glEnd();
  }
};