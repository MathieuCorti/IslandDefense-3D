//
//  Boat.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/7/18.
//

#pragma once

#include "../helpers/Movable.hpp"

class Boat : public Movable {
public:
  
  Boat(const Color color);
  
  void draw() const override;

  void update() override;
};

