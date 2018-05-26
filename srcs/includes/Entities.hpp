//
// Created by wilmot_g on 30/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

template<class T>
class Entities : public Displayable, public Alive {
public:
  //Typedef

  explicit Entities(const Color &color = Color(1, 1, 1)) : Alive(1), _color(color) {
    for (auto &subEntity : _entities) {
    }
  }

  void draw() const override {
    for (auto &e : _entities) {
      e->draw();
    }
  }

  void add(const std::shared_ptr<T> entity) {
    if (!std::is_base_of<Alive, T>::value) {
      throw std::runtime_error("Every member of entities should be from base class Alive");
    }
    if (entity) {
      _entities.push_back(entity);
    }
  }

  void update() override {
    for (auto it = _entities.begin(); it != _entities.end();) {
      it->get()->update();
      if (it->get()->getCurrentHealth() == 0) {
        it = _entities.erase(it);
      } else {
        ++it;
      }
    }
  }

private:
  Color _color;
  std::vector<std::shared_ptr<T> > _entities;
};
