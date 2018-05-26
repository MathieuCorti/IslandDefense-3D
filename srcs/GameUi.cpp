//
//  UI.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#include <utility>

#include <iostream>
#include "includes/GameUi.hpp"

GameUi::GameUi(Entities &entities) : _entities(entities) {}

void GameUi::draw() const {
  for (int i = 0; i < _entities.size(); ++i) {
    glBegin(GL_QUADS);
    glColor4f(_entities[i].second.r, _entities[i].second.g, _entities[i].second.b, _entities[i].second.a);
    float delta = i / 10.0f == 0 ? 0 : i / 10.0f;
    double barLength = -1 * (0.4 + 5 * ((100 - _entities[i].first->getPercentHealthLeft()) / 1000));
    glVertex3d(-0.94, 0.9 - delta, -0.8);
    glVertex3d(-0.94, 0.84 - delta, -0.8);
    glVertex3d(barLength, 0.84 - delta, -0.8);
    glVertex3d(barLength, 0.9 - delta, -0.8);
    glEnd();
  }
}