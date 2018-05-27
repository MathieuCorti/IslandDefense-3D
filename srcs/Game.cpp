//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include <random>

#include "helpers/Axes.hpp"
#include "includes/Game.hpp"
#include "includes/Camera.hpp"
#include "includes/Skybox.hpp"
#include "includes/Stats.hpp"
#include "includes/Island.hpp"
#include "includes/Boat.hpp"
#include "includes/Light.hpp"
#include "includes/GameUi.hpp"

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
//  static Boat::Ptr boat1 = std::dynamic_pointer_cast<Boat>(_entities[BOAT1]);
//  static Boat::Ptr boat2 = std::dynamic_pointer_cast<Boat>(_entities[BOAT2]);
//
//  for (auto &thisShape: boat1->getShapes()) {               // Get the shapes of the projectile
//    for (auto &enemyShape: boat2->getShapes()) {            // Get the shapes of the sub entity
//      if (enemyShape.collideWith(thisShape)) {              // Check collision
//        std::cout << "BOATS COLLIDE !!!!" << std::endl;
//      }
//    }
//  }
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
  setCannonRotation<Island>(GameEntity::ISLAND, camera->getYRot(), camera->getXRot());
}

void Game::mouseClick(int button, int state) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    fire<Island>(GameEntity::ISLAND);
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    defend<Island>(GameEntity::ISLAND);
  }
}

// PRIVATE

void Game::initKeyboardMap() {
  _keyboardMap = {
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},


      // CAMERA COMMANDS TODO : figure if we leave them
      {'a', [this](int, int) { move(GameEntity::CAMERA, LEFT); }},
      {'d', [this](int, int) { move(GameEntity::CAMERA, RIGHT); }},
      {'w', [this](int, int) { move(GameEntity::CAMERA, FORWARD); }},
      {'s', [this](int, int) { move(GameEntity::CAMERA, BACKWARD); }},
      {'A', [this](int, int) { move(GameEntity::CAMERA, LEFT, 3); }},
      {'D', [this](int, int) { move(GameEntity::CAMERA, RIGHT, 3); }},
      {'W', [this](int, int) { move(GameEntity::CAMERA, FORWARD, 3); }},
      {'S', [this](int, int) { move(GameEntity::CAMERA, BACKWARD, 3); }},

      // GRAPHICAL COMMANDS
      {'n', [this](int, int) { _showNormal = !_showNormal; }},
      {'t', [this](int, int) { _showTangeant = !_showTangeant; }},
      {'i', [this](int, int) { _showWireframe = !_showWireframe; }},
      {'l', [this](int, int) { _showLight = !_showLight; }},

      // WAVES COMMANDS
      {'p', [this](int, int) { toggleAnimation(GameEntity::WAVES); }},
      {'+', [this](int, int) { doubleVertices(GameEntity::WAVES); }},
      {'-', [this](int, int) { halveSegments(GameEntity::WAVES); }},

      // ISLAND COMMANDS
      {'e', [this](int, int) { changeCannonPower<Island>(GameEntity::ISLAND, INC_SPEED); }},
      {'r', [this](int, int) { changeCannonPower<Island>(GameEntity::ISLAND, DEC_SPEED); }},
      // ISLAND MOUSE COMMANDS ALTERNATIVE
      {'g', [this](int, int) { fire<Island>(GameEntity::ISLAND); }},
      {'b', [this](int, int) { defend<Island>(GameEntity::ISLAND); }},
      {'h', [this](int, int) { changeCannonDirection<Island>(GameEntity::ISLAND, INC_ROTATION); }},
      {'H', [this](int, int) { changeCannonDirection<Island>(GameEntity::ISLAND, DEC_ROTATION); }},
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
  glutMouseFunc(mouseClickCallback);
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
  auto island = std::make_shared<Island>();
  GameUi::Entities entities = { std::make_pair(std::dynamic_pointer_cast<Alive>(island), GREEN) };
  _entities.insert(std::make_pair(GameEntity::ISLAND, island));
  _entities.insert(std::make_pair(GameEntity::BOATS, generateBoats()));
  _entities.insert(std::make_pair(GameEntity::UI, std::make_shared<GameUi>(entities)));
  _entities.insert(std::make_pair(GameEntity::AXES, std::make_shared<Axes>()));
}

std::shared_ptr<Entities<Boat> > Game::generateBoats() {

  std::random_device rd, rdMin, rdx, rdz;
  std::mt19937 gen(rd()), genMin(rdMin()), genX(rdx()), genZ(rdz());
  std::uniform_real_distribution<float> dis(0.2f, 0.8f);
  std::bernoulli_distribution disMinus(0.5);
  std::uniform_real_distribution<float> disColor(0.0f, 1.0f);

  auto boats = std::make_shared<Entities<Boat> >();
  for (int i = 0; i < NBR_BOATS; ++i) {
    boats->add(std::make_shared<Boat>(Color(disColor(gen), disColor(gen), disColor(gen), 1.0f),
                                      Vector3f(disMinus(genMin) != 0 ? dis(genX) : -dis(genX),
                                               0.0f,
                                               disMinus(genMin) != 0 ? dis(genZ) : -dis(genZ))));
  }
  
  return boats;
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

const bool Game::getShowLight() const {
  return _showLight;
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
static void mouseClickCallback(int button, int state, int x, int y) {
  Game::getInstance().mouseClick(button, state);
}
}