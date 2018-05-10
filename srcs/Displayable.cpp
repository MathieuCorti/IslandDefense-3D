//
// Created by wilmot_g on 02/04/18.
//

#include "helpers/Shape.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

void Displayable::draw() const {
  for (Shape shape: _shapes) {
    glBegin(shape._mode);
    shape.applyColor();
    for (Triangle &t : shape._parts) {
      glNormal3f(t.v1->n.x, t.v1->n.y, t.v1->n.z);
      glVertex3f(t.v1->p.x, t.v1->p.y, t.v1->p.z);
      glNormal3f(t.v2->n.x, t.v2->n.y, t.v2->n.z);
      glVertex3f(t.v2->p.x, t.v2->p.y, t.v2->p.z);
      glNormal3f(t.v3->n.x, t.v3->n.y, t.v3->n.z);
      glVertex3f(t.v3->p.x, t.v3->p.y, t.v3->p.z);
    }
    glEnd();
  }

  if (Game::getInstance().getShowNormal()) {
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    for (const Shape &row : _shapes) {
      for (const Triangle &t : row._parts) {
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        Axes::drawVector(t.v1->p, t.v1->n, 0.1f, true);
        Axes::drawVector(t.v2->p, t.v2->n, 0.1f, true);
        Axes::drawVector(t.v3->p, t.v3->n, 0.1f, true);
      }
    }
    glEnd();
  }
}

const Shapes &Displayable::getShapes() const {
  return _shapes;
}

bool Displayable::isDisplayed() const {
  return _isDisplayed;
}
