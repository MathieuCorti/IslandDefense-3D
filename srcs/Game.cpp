//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>

#include "includes/Game.hpp"
#include "includes/Stats.hpp"
#include "includes/Waves.hpp"

// PUBLIC
int Game::start(int argc, char **argv) {
  // Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
  glutCreateWindow(GAME_NAME);

  // Start
  initDrawCallback();
  initKeyboardCallback();
  initKeyboardMap();
  initGlut();
  initEntities();
  glutIdleFunc(idleFunc);
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::idleFunc() {
  Game::getInstance().update();
  glutPostRedisplay();
}

bool Game::gameOver() const {
  return false;
}

void Game::update() {
  if (gameOver()) {
    return;
  }

  updateTime();

  // Update entities
  for (auto it = _entities.cbegin(); it != _entities.cend();) {
    if (it->second->update()) {
      it = _entities.erase(it++);
    } else {
      ++it;
    }
  }
}

void Game::draw() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);

  if (gameOver()) {
  } else {
    for (const auto &entity : _entities) {
      entity.second->draw();
      for (GLenum err = 0; (err = glGetError());) {
        printf("%s\n", gluErrorString(err));
      }
    }
  }

  _frames++;

  glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y) const {
  if (key != 'q' && key != 27 && gameOver()) {
    return;
  }

  switch (glutGetModifiers()) {
    case GLUT_ACTIVE_SHIFT:
      key = static_cast<unsigned char>(toupper(key));
      break;
    default:
      break;
  }
  auto iter = _keyboardMap.find(key);
  if (iter != _keyboardMap.end()) {
    iter->second.operator()(x, y);
  }
}

// PRIVATE

void Game::initKeyboardMap() {
  _keyboardMap = {
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},

      // WAVES COMMANDS
      {'n', [this](int, int) { toggleNormals(WAVES); }},
      {'t', [this](int, int) { toggleTangeants(WAVES); }},
      {'w', [this](int, int) { toggleWireframe(WAVES); }},
      {'+', [this](int, int) { doubleVertices(WAVES); }},
      {'-', [this](int, int) { halveSegments(WAVES); }}
  };
}

void Game::initDrawCallback() const {
  glutDisplayFunc(drawCallback);
}

void Game::initKeyboardCallback() const {
  glutKeyboardFunc(keyboardCallback);
}

void Game::initGlut() {
  glMatrixMode(GL_PROJECTION);
  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initEntities() {
  _entities.insert(std::make_pair(GameEntity::STATS, std::make_shared<Stats>()));
  _entities.insert(std::make_pair(GameEntity::WAVES, std::make_shared<Waves>()));
//  _entities.insert(std::make_pair(GameEntity::AXES, std::make_shared<Axes>()));
}

const float Game::getTime() const {
  return _time / SPEED;
}

const float &Game::getDeltaTime() const {
  return _deltaTime;
}

void Game::updateTime() {
  _time = glutGet(GLUT_ELAPSED_TIME) / MILLI;

  if (_lastTime == 0.0) {
    _lastTime = _time;
    return;
  }

  _lastTime = _time;


  _deltaTime = _time - _lastFrameRateT;
  if (_deltaTime > _frameRateInterval) {
    _frameRate = _frames / _deltaTime;
    _lastFrameRateT = _time;
    _frames = 0;
  }
}

const float &Game::getFrameRate() const {
  return _frameRate;
}

const Game::EntityList &Game::getEntities() const {
  return _entities;
}

// EXTERN C
extern "C" {
static void drawCallback() {
  Game::getInstance().draw();
}
static void keyboardCallback(unsigned char key, int x, int y) {
  Game::getInstance().keyboard(key, x, y);
}
}