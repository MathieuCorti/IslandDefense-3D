//
//  Glut.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/15/18.
//

#pragma once

#if __APPLE__
#   include <GLUT/glut.h>
#   include <OpenGL/OpenGL.h>
#else
#   include <GL/glu.h>
#   include <GL/glut.h>
#   include <GL/gl.h>
#endif