//
//  Stats.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "Config.hpp"

class Stats : public Displayable {
private:
  Color _color;

public:
  explicit Stats(const Color &color = YELLOW);

  bool update() override { return false; }

  void draw() const override;
};
