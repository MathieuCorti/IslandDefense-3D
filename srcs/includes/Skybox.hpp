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

  GLuint loadTexture(const char *filename);

  GLuint _texture[6] {};
};