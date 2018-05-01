//
//  Camera.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include "helpers/Glut.hpp"
#include "includes/Camera.hpp"

Camera::Camera(): Movable(CAMERA_SPEED, Vector3f(0, 0.1, 0)) {
// GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
// GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
// GLdouble upX, GLdouble upY, GLdouble upZ
}

bool Camera::update() {
  std::cout << "x: " << _coordinates.x << " | "
            << "y: " << _coordinates.y << " | "
            << "z: " << _coordinates.z << " | " << std::endl;
  gluLookAt( _coordinates.x, _coordinates.y, -1.0f,
             1.0f, 1.0f,  1.0f,
             0.0f, 1.0f,  0.0f);
  return false;
}
