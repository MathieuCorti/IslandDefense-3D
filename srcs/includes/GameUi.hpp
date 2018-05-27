//
//  UI.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/30/18.
//

#pragma once


#include "../helpers/Displayable.hpp"
#include "Shape.hpp"
#include "../helpers/Alive.hpp"

class GameUi : public Displayable {

public:
  typedef std::vector<std::pair<AlivePtr, Color> > Entities;

  explicit GameUi(Entities &entities);

  void draw() const override;

private:
  Entities _entities;

};

