//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include <cmath>
#include "Glut.hpp"
#include "Displayable.hpp"
#include "SOIL.h"

class Skybox : public Displayable {
public:

  Skybox() {
    _texture[0] = loadTexture("./assets/sbw.png");
    _texture[1] = loadTexture("./assets/sbs.png");
    _texture[2] = loadTexture("./assets/sbe.png");
    _texture[3] = loadTexture("./assets/sbn.png");
    _texture[4] = loadTexture("./assets/sbt.png");
    _texture[5] = loadTexture("./assets/sbb.png");
  }

  void draw() const override {
//    return;
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    glColor4f(1, 1, 1, 1);

    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, _texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(1.0f, -0.5f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0f, -0.5f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(-1.0f, 1.5f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, _texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.0f, -0.5f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, _texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0f, 1.5f, 1.0f);
    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, _texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0f, -0.5f, -1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(-1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(-1.0f, 1.5f, 1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0f, 1.5f, -1.0f);
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, _texture[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0f, 1.5f, -1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0f, 1.5f, 1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.0f, 1.5f, 1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(1.0f, 1.5f, -1.0f);
    glEnd();

    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, _texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0f, -0.5f, -1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(1.0f, -0.5f, 1.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.0f, -0.5f, -1.0f);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
  }

private:

  GLuint loadTexture(const char *filename) {
    GLuint tex = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    if (!tex) {
      std::cout << "error" << std::endl;
      return 0;
    }

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
  }

  GLuint _texture[6] {};
};