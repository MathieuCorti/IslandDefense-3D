//
//  Camera.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include "helpers/Glut.hpp"
#include "includes/Camera.hpp"
#include "includes/Game.hpp"

Camera::Camera() : Movable(CAMERA_TRANSLATION_SPEED, Vector3f(-0.8f, 0.53f, -0.30f)),
                   _xRot(CAMERA_X_ROT_START), _yRot(CAMERA_Y_ROT_START),
                   _rotationSpeed(CAMERA_ROTATION_SPEED),
                   _lastMouseX(0), _lastMouseY(0) {
}

void Camera::draw() const {
  glRotatef(_xRot, 1.0, 0.0, 0.0);
  glRotatef(_yRot, 0.0, 1.0, 0.0);
  glTranslatef(-_coordinates.x, -_coordinates.y, -_coordinates.z);
}

void Camera::rotation(int x, int y) {
  int diffX = x - _lastMouseX;
  int diffY = y - _lastMouseY;
  _xRot += (float) diffY;
  _yRot += (float) diffX;
  _xRot = _xRot > 90 ? 90 : _xRot;
  _xRot = _xRot < -90 ? -90 : _xRot;
  _lastMouseX = x;
  _lastMouseY = y;
}

void Camera::move(Direction direction, int coef) {
  float xRotRad, yRotRad;

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
      yRotRad = (_yRot / 180.0f * (float) M_PI);
      _coordinates.x -= std::cos(yRotRad) * _speed * _time * coef;
      _coordinates.z -= std::sin(yRotRad) * _speed * _time * coef;
      break;
    case RIGHT:
      yRotRad = (_yRot / 180.0f * (float) M_PI);
      _coordinates.x += std::cos(yRotRad) * _speed * _time * coef;
      _coordinates.z += std::sin(yRotRad) * _speed * _time * coef;
      break;
    case FORWARD:
      yRotRad = (_yRot / 180.0f * (float) M_PI);
      xRotRad = (_xRot / 180.0f * (float) M_PI);
      _coordinates.x += std::sin(yRotRad) * _speed * _time * coef;
      _coordinates.z -= std::cos(yRotRad) * _speed * _time * coef;
      _coordinates.y -= std::sin(xRotRad) * _speed * _time * coef;
      break;
    case BACKWARD:
      yRotRad = (_yRot / 180.0f * (float) M_PI);
      xRotRad = (_xRot / 180.0f * (float) M_PI);
      _coordinates.x -= std::sin(yRotRad) * _speed * _time;
      _coordinates.z += std::cos(yRotRad) * _speed * _time;
      _coordinates.y += std::sin(xRotRad) * _speed * _time;
      break;
  }
}

void Camera::update() {
  _time = Game::getInstance().getDeltaTime();
}
