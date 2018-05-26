//
// Created by wilmot_g on 30/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

template<class T>
class Entities : public Displayable, public Alive {
public:

  explicit Entities() : Alive(1) {
    isAlive = std::is_base_of<Alive, T>::value;
  }

  void draw() const override {
    for (auto &e : _entities) {
      e->draw();
    }
  }

  void add(const std::shared_ptr<T> entity) {
    if (entity) {
      _entities.push_back(entity);
    }
  }

  void update() override {
    for (auto it = _entities.begin(); it != _entities.end();) {
      it->get()->update();
      if (isAlive && it->get()->getCurrentHealth() == 0) {
        it = _entities.erase(it);
      } else {
        ++it;
      }
    }
  }

private:
  std::vector<std::shared_ptr<T> > _entities;
  bool isAlive;
};
