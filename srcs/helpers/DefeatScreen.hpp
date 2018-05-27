//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include <cmath>
#include <cstring>
#include "Glut.hpp"
#include "Displayable.hpp"
#include "../includes/Waves.hpp"
#include "../includes/Game.hpp"

class DefeatScreen : public Displayable {
public:

  DefeatScreen(const std::string &message, const Color &color) : _message(message), _color(color) {}

  void draw() const override {
    char buffer[30];
    char *bufp;
    int w, h;

    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(_color.r, _color.g, _color.b);
    snprintf(buffer, sizeof buffer, "%s", _message.c_str());
    glRasterPos2i(static_cast<GLint>(w / 2 - 12 * strlen(buffer) / 2), h / 2 - 12);
    for (bufp = buffer; *bufp; bufp++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *bufp);
    }

    glColor3f(_color.r, _color.g, _color.b);
    snprintf(buffer, sizeof buffer, "%s", "Press esc to quit");
    glRasterPos2i(static_cast<GLint>(w / 2 - 12 * strlen(buffer) / 2), h / 2 - 40);
    for (bufp = buffer; *bufp; bufp++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *bufp);
    }


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();
  }

private:
  std::string _message;
  Color _color;
};