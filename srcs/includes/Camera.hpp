//
//  Camera.hpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#pragma once

#include "../helpers/Glut.hpp"
#include "../helpers/Movable.hpp"
#include "../helpers/Displayable.hpp"

class Camera: public Movable {
private:
  
public:

  Camera();
  
  bool update() override;
};

