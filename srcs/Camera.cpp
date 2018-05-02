//
//  Camera.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include "helpers/Glut.hpp"
#include "includes/Camera.hpp"

Camera::Camera(): Movable(CAMERA_SPEED, Vector3f(0, 0.1, 0)), 
                  _psi(float(4 * M_PI / 7)), _theta(float(M_PI / 4)), 
                  _rotationSpeed(0.01), _translationSpeed(0.2),
                  _lastMouseX(GAME_WIDTH / 2), _lastMouseY(GAME_HEIGHT / 2),
                  _coef(1000) {
}

bool Camera::update() {
  return false;
}

void Camera::draw() const {
  auto sight = getSight();
//  std::cout << "x: " << _coordinates.x << " | "
//            << "y: " << _coordinates.y << " | "
//            << "z: " << _coordinates.z << " | " << std::endl;
  gluLookAt( _coordinates.x, _coordinates.y, _coordinates.z,
             sight.x, sight.y, sight.z,
             0, 1.0f, 0);
}

void Camera::rotation(int x, int y) {
  _theta -= static_cast<float>(x - _lastMouseX) * _rotationSpeed;
  _psi += static_cast<float>(y - _lastMouseY) * _rotationSpeed;
  if(_psi <= 0.1) {
    _psi = 0.1;
  } else if(_psi >= 0.95 * M_PI) {
    _psi = float(0.95 * M_PI);
  }
  _lastMouseX = x;
  _lastMouseY = y;
}

void Camera::move(Direction direction) {
  auto t = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) - _time);
  _time = glutGet(GLUT_ELAPSED_TIME);

  switch (direction) {
    case UP:
//      setY(getCoordinates().y + getSpeed());
      break;
    case DOWN:
//      setY(getCoordinates().y - getSpeed());
      break;
    case LEFT:
      _coordinates.x -= (sin(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t) / _coef;
      _coordinates.z -= (cos(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t) / _coef;
      break;
    case RIGHT:
      _coordinates.x -= (sin(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t) / _coef;
      _coordinates.z -= (cos(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t) / _coef;
      break;
    case FORWARD:
      _coordinates.x += (sin(_theta)*sin(_psi)  * _translationSpeed * t) / _coef;
      _coordinates.y += (cos(_psi)              * _translationSpeed * t) / _coef;
      _coordinates.z += (cos(_theta)*sin(_psi)  * _translationSpeed * t) / _coef;
      break;
    case BACKWARD:
      _coordinates.x -= (sin(_theta)*sin(_psi)  * _translationSpeed * t) / _coef;
      _coordinates.y -= (cos(_psi)              * _translationSpeed * t) / _coef;
      _coordinates.z -= (cos(_theta)*sin(_psi)  * _translationSpeed * t) / _coef;
      break;
  }
}
