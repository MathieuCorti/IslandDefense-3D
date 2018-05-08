//
//  Boat.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/7/18.
//

#include "includes/Boat.hpp"
#include "includes/Waves.hpp"

Boat::Boat(const Color color) : Movable(0.05f, Vector3f(0.3f, 0.0f, 0.0f)) {
  _shapes.push_back(Shape({
                            // TOP
                            Vector3f( 0.1f, 0.05f, -0.05f),
                            Vector3f(-0.1f, 0.05f, -0.05f),
                            Vector3f(-0.1f, 0.05f,  0.05f),
                            Vector3f( 0.1f, 0.05f,  0.05f),
                            
                            // FRONT
                            Vector3f( 0.1f,  0.05f, 0.05f),
                            Vector3f(-0.1f,  0.05f, 0.05f),
                            Vector3f( 0.0f, -0.05f, 0.05f),
                            Vector3f( 0.0f, -0.05f, 0.05f),
                            
                            // BACK
                            Vector3f( 0.0f, -0.05f, -0.05f),
                            Vector3f( 0.0f, -0.05f, -0.05f),
                            Vector3f(-0.1f,  0.05f, -0.05f),
                            Vector3f( 0.1f,  0.05f, -0.05f),
                            
                            // LEFT
                            Vector3f(-0.1f,  0.05f,  0.05f),
                            Vector3f(-0.1f,  0.05f, -0.05f),
                            Vector3f(-0.0f, -0.05f, -0.05f),
                            Vector3f(-0.0f, -0.05f,  0.05f),
                            
                            // RIGHT
                            Vector3f(0.1f,  0.05f, -0.05f),
                            Vector3f(0.1f,  0.05f,  0.05f),
                            Vector3f(0.0f, -0.05f,  0.05f),
                            Vector3f(0.0f, -0.05f, -0.05f)
                          }, GL_POLYGON, color));

}

void Boat::draw() const {
  glEnable(GL_BLEND);
  Displayable::draw();
}

void Boat::update() {
  _coordinates.y = Waves::computeHeight(_coordinates.x, _coordinates.z);
}
