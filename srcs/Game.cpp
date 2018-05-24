//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>

#include "helpers/Axes.hpp"
#include "includes/Game.hpp"
#include "includes/Camera.hpp"
#include "includes/Skybox.hpp"
#include "includes/Stats.hpp"
#include "includes/Island.hpp"
#include "includes/Boat.hpp"
#include "includes/Light.hpp"

// PUBLIC
int Game::start(int argc, char **argv) {
  // Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
  glutCreateWindow(GAME_NAME);

  // Start
  initDrawCallback();
  initReshapeCallback();
  initKeyboardCallback();
  initKeyboardMap();
  initBlend();
  initMouseCallback();
  glutIdleFunc(idleFunc);
  initEntities();
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
    it->second->update();
    if (!it->second->isDisplayed()) {
      it = _entities.erase(it++);
    } else {
      ++it;
    }
  }


  // =============================================== TEST =============================================================
  static Island::Ptr island = std::dynamic_pointer_cast<Island>(_entities[ISLAND]);
  static Boat::Ptr boat = std::dynamic_pointer_cast<Boat>(_entities[BOAT]);

  for (auto &thisShape: island->getShapes()) {               // Get the shapes of the projectile
    for (auto &enemyShape: boat->getShapes()) {              // Get the shapes of the sub entity
      if (enemyShape.collideWith(thisShape)) {               // Check collision
        std::cout << "BOAT COLLIDE WITH ISLAND !!!!" << std::endl;
      }
    }
  }
  // =============================================== TEST =============================================================
}

void Game::draw() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75.0f, 1.0f, 0.01f, 3.0f);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_DEPTH_TEST);

  if (_showWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (!gameOver()) {
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

void Game::mouse(int x, int y) {
  static auto camera = std::dynamic_pointer_cast<Camera>(_entities[GameEntity::CAMERA]);
  camera->rotation(x, y);
}

// PRIVATE

void Game::initKeyboardMap() {
  _keyboardMap = {
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},

      {'a', [this](int, int) { move(GameEntity::CAMERA, LEFT); }},
      {'d', [this](int, int) { move(GameEntity::CAMERA, RIGHT); }},
      {'w', [this](int, int) { move(GameEntity::CAMERA, FORWARD); }},
      {'s', [this](int, int) { move(GameEntity::CAMERA, BACKWARD); }},
      {'q', [this](int, int) { move(GameEntity::CAMERA, UP); }},
      {'e', [this](int, int) { move(GameEntity::CAMERA, DOWN); }},
      {'A', [this](int, int) { move(GameEntity::CAMERA, LEFT, 3); }},
      {'D', [this](int, int) { move(GameEntity::CAMERA, RIGHT, 3); }},
      {'w', [this](int, int) { move(GameEntity::CAMERA, FORWARD, 3); }},
      {'S', [this](int, int) { move(GameEntity::CAMERA, BACKWARD, 3); }},
      {'Q', [this](int, int) { move(GameEntity::CAMERA, UP, 3); }},
      {'E', [this](int, int) { move(GameEntity::CAMERA, DOWN, 3); }},

      {'n', [this](int, int) { _showNormal = !_showNormal; }},
      {'t', [this](int, int) { _showTangeant = !_showTangeant; }},
      {'W', [this](int, int) { _showWireframe = !_showWireframe; }},

      // WAVES COMMANDS
      {'p', [this](int, int) { toggleAnimation(GameEntity ::WAVES); }},
      {'+', [this](int, int) { doubleVertices(GameEntity ::WAVES); }},
      {'-', [this](int, int) { halveSegments(GameEntity ::WAVES); }},

      // TEST BOAT COMMANDS
      {'j', [this](int, int) { move(GameEntity::BOAT, LEFT); }},
      {'l', [this](int, int) { move(GameEntity::BOAT, RIGHT); }},
      {'i', [this](int, int) { move(GameEntity::BOAT, FORWARD); }},
      {'k', [this](int, int) { move(GameEntity::BOAT, BACKWARD); }}
  };
}

void Game::initDrawCallback() const {
  glutDisplayFunc(drawCallback);
}

void Game::initReshapeCallback() const {
  glutReshapeFunc(reshapeCallback);
}

void Game::initKeyboardCallback() const {
  glutKeyboardFunc(keyboardCallback);
}

void Game::initMouseCallback() const {
  glutPassiveMotionFunc(mouseCallback);
}

void Game::initBlend() {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initEntities() {
  _entities.insert(std::make_pair(GameEntity::CAMERA, std::make_shared<Camera>()));
  _entities.insert(std::make_pair(GameEntity::LIGHT, std::make_shared<Light>()));
  _entities.insert(std::make_pair(GameEntity::STATS, std::make_shared<Stats>()));
  _entities.insert(std::make_pair(GameEntity::WAVES, std::make_shared<Waves>()));
  _entities.insert(std::make_pair(GameEntity::SKYBOX, std::make_shared<Skybox>()));
  _entities.insert(std::make_pair(GameEntity::ISLAND, std::make_shared<Island>()));
  _entities.insert(std::make_pair(GameEntity::BOAT, std::make_shared<Boat>(RED)));
  _entities.insert(std::make_pair(GameEntity::AXES, std::make_shared<Axes>()));
}

const float Game::getTime() const {
  return _time / GAME_SPEED;
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

const bool Game::getShowTangeant() const {
  return _showTangeant;
}

const bool Game::getShowNormal() const {
  return _showNormal;
}

// EXTERN C
extern "C" {
static void drawCallback() {
  Game::getInstance().draw();
}
static void reshapeCallback(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75.0f, (GLfloat) w / (GLfloat) h, 0.01f, 3.0);
  glMatrixMode(GL_MODELVIEW);
}
static void keyboardCallback(unsigned char key, int x, int y) {
  Game::getInstance().keyboard(key, x, y);
}
static void mouseCallback(int x, int y) {
  Game::getInstance().mouse(x, y);
}
}