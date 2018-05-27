//
//  Boat.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/7/18.
//

#pragma once

#include "../helpers/Movable.hpp"
#include "Cannon.hpp"

class Boat : public Movable, public Alive {
public:

  explicit Boat(Color color, Vector3f startPos);

  void draw() const override;

  void update() override;

  Cannon::Ptr getCannon() const;

  const std::list<Displayable *> &getCollidables() override;

private:

  void computeAI(const Vector3f &);

  Cannon::Ptr _cannon;
  float _duration;
};

