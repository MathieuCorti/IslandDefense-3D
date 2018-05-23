//
// Created by wilmot_g on 01/04/18.
//

#include "includes/Pellet.hpp"
#include "includes/Game.hpp"
#include "includes/Projectile.hpp"

Pellet::Pellet(float t, Vector3f coordinates, Color c) : Displayable(coordinates),
                                                                         Alive(1),
                                                                         _color(c),
                                                                         _startT(t),
                                                                         _radius(0) {}

void Pellet::update() {
  if (getCurrentHealth() == 0) {
    return;
  }
  float x = Game::getInstance().getTime() - _startT;
  _radius += 0.00008 / x;
  _shapes.clear();
//  _shapes.push_back(Projectile::getCircle(_radius, _coordinates));
  //TODO : get circle
  if (_radius > 0.2f) {
    _currentHealth = 0;
  }
}

void Pellet::draw() const {
  //TODO
}
