//
// Created by wilmot_g on 01/04/18.
//

#include "includes/Pellet.hpp"
#include "includes/Game.hpp"

Pellet::Pellet(float t, Vector3f coordinates, Cannon *cannon, Color c) : Displayable(coordinates),
                                                                         Alive(1),
                                                                         _color(c),
                                                                         _startT(t),
                                                                         _radius(0),
                                                                         _cannon(cannon) {}

void Pellet::update() {
  if (getCurrentHealth() == 0) {
    return;
  }
  _coordinates.x = _cannon->getCoordinates().x;
  _coordinates.y = _cannon->getCoordinates().y;
  float x = Game::getInstance().getTime() - _startT;
  _radius += 0.00008 / x;
  _shapes.clear();
  _shapes.push_back(Projectile::getCircle(_radius, _coordinates));
  if (_radius > 0.2f) {
    _currentHealth = 0;
  }
}


void Pellet::draw() const {
  //TODO
}
