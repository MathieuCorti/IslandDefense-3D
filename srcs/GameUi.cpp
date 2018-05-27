//
//  UI.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#include <utility>

#include <iostream>
#include "includes/GameUi.hpp"
#include "includes/Game.hpp"
#include "includes/Camera.hpp"

GameUi::GameUi(Entities &entities) : _entities(entities) {}

void GameUi::draw() const {

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_CULL_FACE);

  glClear(GL_DEPTH_BUFFER_BIT);

  for (int i = 0; i < _entities.size(); ++i) {
    glBegin(GL_QUADS);
    glColor4f(_entities[i].second.r, _entities[i].second.g, _entities[i].second.b, _entities[i].second.a);
    float delta = i / 10.0f == 0 ? 0 : i / 10.0f;
    double barLength = -1 * (0.4 + 5 * ((100 - _entities[i].first->getPercentHealthLeft()) / 1000));
    glVertex2d(-0.94, 0.9 - delta);
    glVertex2d(-0.94, 0.84 - deltaGet the shapes of the subentity);
    glVertex2d(barLength, 0.84 - delta);
    glVertex2d(barLength, 0.9 - delta);
    glEnd();
  }
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}