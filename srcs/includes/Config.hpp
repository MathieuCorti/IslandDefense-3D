//
//  Config.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 4/2/18.
//

#pragma once

// GENERAL
#define MILLI 1000.0f

// GAME
#define GAME_NAME "Island Defense 3D"
#define GAME_WIDTH 600
#define GAME_HEIGHT 600
#define GAME_SPEED 3

// CAMERA
#define CAMERA_SPEED 1

// Colors
#define BLACK   Color(0, 0, 0)
#define WHITE   Color(255, 255, 255)
#define RED     Color(255, 0, 0)
#define GREEN   Color(0, 255, 0)
#define YELLOW  Color(255, 255, 0)
#define BLUE    Color(0, 0, 255)

// ENTITIES
enum GameEntity {
  CAMERA,
  LIGHT,
  AXES,
  SKYBOX,
  BOAT,
  ISLAND,
  WAVES,
  STATS,
  UI,
  GAME_ENTITIES_EOF
};