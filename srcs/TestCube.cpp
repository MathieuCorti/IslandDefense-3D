//
//  TestCube.cpp 
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/1/18.
//

#include "includes/TestCube.hpp"
#include "includes/Config.hpp"

TestCube::TestCube() {
  _shapes.push_back(Shape({
                            Vector3f( 0.1f, 0.1f,-0.1f),
                            Vector3f(-0.1f, 0.1f,-0.1f),
                            Vector3f(-0.1f, 0.1f, 0.1f),
                            Vector3f( 0.1f, 0.1f, 0.1f),
                            Vector3f( 0.1f,-0.1f, 0.1f),
                            Vector3f(-0.1f,-0.1f, 0.1f),
                            Vector3f(-0.1f,-0.1f,-0.1f),
                            Vector3f( 0.1f,-0.1f,-0.1f),
                            Vector3f( 0.1f, 0.1f, 0.1f),
                            Vector3f(-0.1f, 0.1f, 0.1f),
                            Vector3f(-0.1f,-0.1f, 0.1f),
                            Vector3f( 0.1f,-0.1f, 0.1f),
                            Vector3f( 0.1f,-0.1f,-0.1f),
                            Vector3f(-0.1f,-0.1f,-0.1f),
                            Vector3f(-0.1f, 0.1f,-0.1f),
                            Vector3f( 0.1f, 0.1f,-0.1f),
                            Vector3f(-0.1f, 0.1f, 0.1f),
                            Vector3f(-0.1f, 0.1f,-0.1f),
                            Vector3f(-0.1f,-0.1f,-0.1f),
                            Vector3f(-0.1f,-0.1f, 0.1f),
                            Vector3f( 0.1f, 0.1f,-0.1f),
                            Vector3f( 0.1f, 0.1f, 0.1f),
                            Vector3f( 0.1f,-0.1f, 0.1f),
                            Vector3f( 0.1f,-0.1f,-0.1f)
                          }, GL_QUADS, BLUE));
}