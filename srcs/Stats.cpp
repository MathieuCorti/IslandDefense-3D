//
//  Stats.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include <cstdio>
#include <cstring>

#include "helpers/Glut.hpp"
#include "includes/Stats.hpp"
#include "includes/Game.hpp"

Stats::Stats(const Color &color) : _color(color) {}

void Stats::draw() const {
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

  auto &game = Game::getInstance();

  /* Frame rate */
  glColor3f(_color.r, _color.g, _color.b);
  snprintf(buffer, sizeof buffer, "fps        : %5.0f", game.getFrameRate());
  glRasterPos2i(static_cast<GLint>(w - 20 - 9 * strlen(buffer)), h - 20);
  for (bufp = buffer; *bufp; bufp++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);
  }

  /* Time per frame */
  glColor3f(_color.r, _color.g, _color.b);
  snprintf(buffer, sizeof buffer, "frame time : %3.0fms", 1.0 / game.getFrameRate() * 1000.0);
  glRasterPos2i(static_cast<GLint>(w - 20 - 9 * strlen(buffer)), h - 40);
  for (bufp = buffer; *bufp; bufp++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);
  }

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glPopAttrib();
}