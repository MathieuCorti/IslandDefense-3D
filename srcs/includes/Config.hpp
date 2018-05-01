//
//  Config.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 4/2/18.
//

#pragma once

// GAME
#define MILLI 1000.0f

// DETAILS
#define ISLAND_COLOR      Color(255, 255, 0)
#define RIGHT_BOAT_COLOR  Color(255, 0, 0)
#define LEFT_BOAT_COLOR   Color(0, 0, 255)
#define BOAT_START_X  0.65
#define CANNON_RIGHT  0.04
#define CANNON_LEFT   -0.04
#define CANNON_ROTATION_LEFT -4.5f
#define CANNON_ROTATION_RIGHT 1.0f
#define INCREASE  0.1f
#define DECREASE  -0.1f
#define INVERTED true
#define STANDARD false
#define BOAT_START_HP 10
#define ISLAND_START_HP 100

// ENTITIES
#define ISLAND      "island"
#define RIGHT_BOAT  "right_boat"
#define LEFT_BOAT   "left_boat"
#define WAVES       "waves"
#define PELLETS     "pellets"
#define STATS       "stats"
#define GAME_UI     "UI"
#define AXES        "axes"
#define LEFT_BOAT_PROJECTILES   "left_boat_projectiles"
#define RIGHT_BOAT_PROJECTILES  "right_boat_projectiles"
#define ISLAND_PROJECTILES      "island_projectiles"