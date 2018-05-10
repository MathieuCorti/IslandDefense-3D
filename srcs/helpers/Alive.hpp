//
//  Alive.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#pragma once

#include "Shape.hpp"

class Alive {

protected:
  const int _totalHealth;
  int _currentHealth;

public:

  explicit Alive(int health) : _currentHealth(health), _totalHealth(health) {}

  int takeDamage(int amount) {
    const int newHealth = getCurrentHealth() - amount;
    return _currentHealth = newHealth < 0 ? 0 : newHealth;
  }

  int getCurrentHealth() {
    return _currentHealth;
  }

  int getTotalHealth() {
    return _totalHealth;
  }

  float getPercentHealthLeft() {
    return static_cast<float>(getCurrentHealth()) / static_cast<float>(getTotalHealth()) * 100.0f;
  }

};

typedef std::shared_ptr<Alive> AlivePtr;