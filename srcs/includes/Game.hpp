//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>

#include "../helpers/Glut.hpp"
#include "../helpers/Displayable.hpp"
#include "../helpers/Movable.hpp"
#include "Config.hpp"
#include "Waves.hpp"

class Game {

// TYPEDEFS
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;
  typedef std::map<GameEntity, Displayable::Ptr> EntityList;

public:
  static Game &getInstance() {
    static Game instance;
    return instance;
  }

  int start(int argc, char **argv);

  void draw();

  void keyboard(unsigned char key, int x, int y) const;
  
  void mouse(int x, int y);

  void mouseButtons(int button, int state, int x, int y) const;

  const float getTime() const;

  const float &getDeltaTime() const;

  const float &getFrameRate() const;
  
  const EntityList &getEntities() const;

  Game(const Game &) = delete;

  Game &operator=(const Game &) = delete;

private:
  KeyboardMap _keyboardMap;
  EntityList _entities;
  float _time, _lastTime, _deltaTime = 0.0;
  float _lastFrameRateT, _frameRateInterval, _frameRate, _frames;

  void initDrawCallback() const;

  void initKeyboardCallback() const;

  void initMouseCallback() const;
  
  void initMouseButtonsCallback() const;

  void initKeyboardMap();

  void initGlut();

  void initEntities();

  void update();

  void updateTime();

  static void idleFunc();

  // Helpers

  void move(const GameEntity &entityName, Direction direction) {
    std::dynamic_pointer_cast<Movable>(_entities[entityName])->move(direction);
  }

  void toggleTangeants(const GameEntity &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleTangeants();
  }

  void toggleNormals(const GameEntity &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleNormals();
  }

  void toggleWireframe(const GameEntity &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->toggleWireframe();
  }

  void doubleVertices(const GameEntity &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->doubleVertices();
  }

  void halveSegments(const GameEntity &entityName) {
    std::dynamic_pointer_cast<Waves>(_entities[entityName])->halveSegments();
  }

  // Singleton
  Game() : _frameRateInterval(0), _time(0), _lastTime(0), _lastFrameRateT(0), _frameRate(0), _frames(0) {}

  ~Game() = default;

  bool gameOver() const;
};

// Extern C
extern "C" {
  static void drawCallback();
  static void keyboardCallback(unsigned char key, int x, int y);
  static void mouseCallback(int x, int y);
  static void mouseButtonsCallback(int button, int state, int x, int y);
}