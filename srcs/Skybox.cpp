//
// Created by wilmot_g on 01/05/18.
//

#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"
#include "includes/Skybox.hpp"

Skybox::Skybox() {
  _texture[0] = TextureLoader::loadTexture("./assets/sbw.png");
  _texture[1] = TextureLoader::loadTexture("./assets/sbs.png");
  _texture[2] = TextureLoader::loadTexture("./assets/sbe.png");
  _texture[3] = TextureLoader::loadTexture("./assets/sbn.png");
  _texture[4] = TextureLoader::loadTexture("./assets/sbt.png");
  _texture[5] = TextureLoader::loadTexture("./assets/sbb.png");
}

void Skybox::draw() const {
  glPushAttrib(GL_ENABLE_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  // Render the front quad
  glBindTexture(GL_TEXTURE_2D, _texture[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(1.0f, -0.8f, -1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(-1.0f, -0.8f, -1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(-1.0f, 1.2f, -1.0f);
  glTexCoord2f(0, 1);
  glVertex3f(1.0f, 1.2f, -1.0f);
  glEnd();

  // Render the left quad
  glBindTexture(GL_TEXTURE_2D, _texture[1]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(1.0f, -0.8f, -1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(1.0f, 1.2f, -1.0f);
  glTexCoord2f(0, 1);
  glVertex3f(1.0f, 1.2f, 1.0f);
  glEnd();

  // Render the back quad
  glBindTexture(GL_TEXTURE_2D, _texture[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(1.0f, 1.2f, 1.0f);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0f, 1.2f, 1.0f);
  glEnd();

  // Render the right quad
  glBindTexture(GL_TEXTURE_2D, _texture[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0f, -0.8f, -1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(-1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(-1.0f, 1.2f, 1.0f);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0f, 1.2f, -1.0f);
  glEnd();

  // Render the top quad
  glBindTexture(GL_TEXTURE_2D, _texture[4]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0f, 1.2f, -1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0f, 1.2f, 1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(1.0f, 1.2f, 1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(1.0f, 1.2f, -1.0f);
  glEnd();

  // Render the bottom quad
  glBindTexture(GL_TEXTURE_2D, _texture[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0f, -0.8f, -1.0f);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 1);
  glVertex3f(1.0f, -0.8f, 1.0f);
  glTexCoord2f(1, 0);
  glVertex3f(1.0f, -0.8f, -1.0f);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopAttrib();
}

GLuint TextureLoader::loadTexture(const char *filename) {
  GLuint tex = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  if (!tex) {
    std::cerr << "error" << std::endl;
    return 0;
  }

  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}
