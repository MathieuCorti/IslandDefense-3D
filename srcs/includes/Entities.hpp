//
// Created by wilmot_g on 30/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

template<class T>
class Entities : public Displayable, public Alive {
public:
  //Typedef
  typedef std::shared_ptr<T> Ptr;

  explicit Entities(const Color &color = Color(1, 1, 1)) : Alive(1), _color(color) {
    for (auto &subEntity : _entities) {
    }
  }

  void draw() const override {
    for (auto &e : _entities) {
      e->draw();
    }
  }

  void add(const T &entity) {
    if (entity) {
      _entities.push_back(entity);
    }
  }

  bool update() override {
    for (auto it = _entities.begin(); it != _entities.end();) {
      if (it->get()->update()) {
        it = _entities.erase(it);
      } else {
        ++it;
      }
    }
    return false;
  }

  const std::list<Displayable *> &getCollidables() override {
    _collidables.clear();
    for (auto &entityBag : _entities) {
      _collidables.push_back(entityBag.get());
      for (auto &entity : entityBag->getCollidables()) {
        _collidables.push_back(entity);
      }
    }
    return _collidables;
  }

private:
  Color _color;
  std::vector<T> _entities;
};
