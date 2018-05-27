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

// BOATS
#define NBR_BOATS 4
#define BOATS_BASE_HEALTH 1

// ISLAND
#define ISLAND_BASE_HEALTH 100

// CANNON
#define INC_SPEED  float(0.1f)
#define DEC_SPEED  (-INC_SPEED)
#define INC_ROTATION  (static_cast<float>(0.05f * 180.0f / M_PI))
#define DEC_ROTATION  (-INC_ROTATION)

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
  BOATS,
  BOAT1,
  BOAT2,
  WAVES,
  STATS,
  UI,
  GAME_ENTITIES_EOF
};