//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include <cmath>
#include "../helpers/Glut.hpp"
#include "../helpers/Displayable.hpp"
#include "../helpers/SOIL.h"

class Skybox : public Displayable {
public:

  Skybox();

  void draw() const override;

private:

  GLuint _texture[6]{};
};

class TextureLoader {
public:
  static GLuint loadTexture(const char *filename);
};