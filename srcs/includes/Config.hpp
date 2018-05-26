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
#define CAMERA_TRANSLATION_SPEED 1.0f
#define CAMERA_ROTATION_SPEED 0.01f
#define CAMERA_X_ROT_START 30.0f
#define CAMERA_Y_ROT_START (-245.0f)

// CANNON
#define INC_SPEED  (0.1f)
#define DEC_SPEED  (-INC_SPEED)
#define INC_ROT  (0.1f * 180.0f / M_PI)
#define DEC_ROT  (-INC_ROT)

// COLORS
#define BLACK   Color(0, 0, 0)
#define WHITE   Color(255, 255, 255)
#define RED     Color(255, 0, 0)
#define GREEN   Color(0, 255, 0)
#define YELLOW  Color(255, 255, 0)
#define BLUE    Color(0, 0, 255)
#define ORANGE  Color(1.0f, 0.5f, 0.0f, 1.0f)
#define GREY    Color(0.75f, 0.75f, 0.75f, 1.0f)

// ENTITIES
enum GameEntity {
  CAMERA,
  LIGHT,
  ISLAND,
  AXES,
  SKYBOX,
  BOAT,
  WAVES,
  STATS,
  UI,
  GAME_ENTITIES_EOF
};