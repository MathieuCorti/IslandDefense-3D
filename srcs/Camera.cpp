//
//  Camera.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include "helpers/Glut.hpp"
#include "includes/Camera.hpp"
#include "includes/Game.hpp"

Camera::Camera() : Movable(CAMERA_SPEED, Vector3f(0.5f, 0.8f, 0.5f)),
                   _xRot(45.0f), _yRot(-45.0f),
                   _rotationSpeed(0.01), _translationSpeed(1.0f),
                   _lastMouseX(0), _lastMouseY(0) {
}

void Camera::draw() const {
  glRotatef(_xRot, 1.0, 0.0, 0.0);
  glRotatef(_yRot, 0.0, 1.0, 0.0);
  glTranslatef(-_coordinates.x, -_coordinates.y, -_coordinates.z);
}

void Camera::rotation(int x, int y) {
  int diffx = x - _lastMouseX;
  int diffy = y - _lastMouseY;
  _xRot += (float) diffy;
  _yRot += (float) diffx;
  _xRot = _xRot > 90 ? 90 : _xRot;
  _xRot = _xRot < -90 ? -90 : _xRot;
  _lastMouseX = x;
  _lastMouseY = y;
}

void Camera::move(Direction direction, int coef) {
  float xrotrad, yrotrad;

  switch (direction) {
    case UP:
      _xRot += 1;
      _xRot = _xRot > 90 ? 90 : _xRot * coef;
      break;
    case DOWN:
      _xRot -= 1;
      _xRot = _xRot < -90 ? -90 : _xRot * coef;
      break;
    case LEFT:
      yrotrad = (_yRot / 180.0f * (float) M_PI);
      _coordinates.x -= std::cos(yrotrad) * _translationSpeed * _time * coef;
      _coordinates.z -= std::sin(yrotrad) * _translationSpeed * _time * coef;
      break;
    case RIGHT:
      yrotrad = (_yRot / 180.0f * (float) M_PI);
      _coordinates.x += std::cos(yrotrad) * _translationSpeed * _time * coef;
      _coordinates.z += std::sin(yrotrad) * _translationSpeed * _time * coef;
      break;
    case FORWARD:
      yrotrad = (_yRot / 180.0f * (float) M_PI);
      xrotrad = (_xRot / 180.0f * (float) M_PI);
      _coordinates.x += std::sin(yrotrad) * _translationSpeed * _time * coef;
      _coordinates.z -= std::cos(yrotrad) * _translationSpeed * _time * coef;
      _coordinates.y -= std::sin(xrotrad) * _translationSpeed * _time * coef;
      break;
    case BACKWARD:
      yrotrad = (_yRot / 180.0f * (float) M_PI);
      xrotrad = (_xRot / 180.0f * (float) M_PI);
      _coordinates.x -= std::sin(yrotrad) * _translationSpeed * _time;
      _coordinates.z += std::cos(yrotrad) * _translationSpeed * _time;
      _coordinates.y += std::sin(xrotrad) * _translationSpeed * _time;
      break;
  }
}

bool Camera::update() {
  _time = Game::getInstance().getDeltaTime();
  return false;
}
