//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

#define PROJECTILE_DAMAGES 1

Projectile::Projectile(float t, Vector3f coordinates, Vector3f velocity, Color c) : Displayable(coordinates),
                                                                                    Alive(1),
                                                                                    _color(c),
                                                                                    _startT(t),
                                                                                    _start(coordinates),
                                                                                    _velocity(velocity) {
  Triangles triangles;
  Shape shape = Shape(triangles, _coordinates, GL_TRIANGLES, BLACK);
  _shapes.push_back(shape);
}

void Projectile::updateShape(float radius) {
  Vertices vertices;
  int numSlices = 20;
  int numSegments = 20;
  Vector3f p, n;
  for (int i = 0; i < numSlices; i++) {
    std::vector<Vertex::Ptr> points;
    auto phi = static_cast<float>(i * (2.0f * M_PI / numSlices));
    for (int j = 0; j < numSegments; j++) {
      float xzRadius = fabsf(radius * cosf(phi));
      auto theta = static_cast<float>(j * (2.0f * M_PI / numSegments));
      p.x = xzRadius * cosf(theta);
      p.y = radius * sinf(phi);
      p.z = xzRadius * sinf(theta);
      float fRcpLen = 1.0f / sqrtf((p.x * p.x) + (p.y * p.y) + (p.z * p.z));
      n.x = p.x * fRcpLen;
      n.y = p.y * fRcpLen;
      n.z = p.z * fRcpLen;
      points.push_back(std::make_shared<Vertex>(p, n));
      if (i == 0 || i == numSlices - 1) {
        break;
      }
    }
    vertices.push_back(points);
  }

  Triangles triangles;
  for (int i = 0; i < vertices.size() - 1; i++) {
    Vertex::Ptr bl = vertices[i][vertices[i].size() - 1];
    Vertex::Ptr br = vertices[i][0];
    Vertex::Ptr tl = vertices[i + 1][vertices[i + 1].size() - 1];
    Vertex::Ptr tr = vertices[i + 1][0];
    triangles.emplace_back(bl, tl, tr);
    triangles.emplace_back(tr, br, bl);
    for (int j = 0; j < vertices[i].size() - 1; j++) {
      bl = vertices[i][vertices[i].size() == 1 ? 0 : j];
      br = vertices[i][vertices[i].size() == 1 ? 0 : j + 1];
      tl = vertices[i + 1][vertices[i + 1].size() == 1 ? 0 : j];
      tr = vertices[i + 1][vertices[i + 1].size() == 1 ? 0 : j + 1];
      triangles.emplace_back(bl, tl, tr);
      triangles.emplace_back(tr, br, bl);
    }
  }

  Shape shape = Shape(triangles, GL_TRIANGLES, _color);
  _shapes.clear();
  _shapes.emplace_back(shape);
}

void Projectile::update() {
  if (getCurrentHealth() == 0) {
    return;
  }

  updateShape(0.02f);

  float t = Game::getInstance().getTime() - _startT;
  _coordinates.x = _start.x + _velocity.x * t;
  _coordinates.y = _start.y + _velocity.y * t + g * t * t / 2.0f;
  _coordinates.z = _start.z + _velocity.z * t;
  float wave = Waves::computeHeight(_coordinates.x, _coordinates.z);

  auto entities = Game::getInstance().getEntities();                      //Get all entities
  for (auto &entityBag: entities) {                                       //Get one entity
    for (auto entity : entityBag.second->getCollidables()) {              //Get all the subentities
      if (entity != this) {                                               //Do not collide with yourself
        auto aliveEntity = dynamic_cast<Alive *>(entity);                 //Can it be collided with ?
        if (aliveEntity != nullptr) {
          for (auto &thisShape: _shapes) {                                //Get the shapes of the projectile
            for (auto &enemyShape: entity->getShapes()) {                 //Get the shapes of the subentity
              if (enemyShape.collideWith(thisShape)) {                    //Check collision
                aliveEntity->takeDamage(PROJECTILE_DAMAGES);              //Deal damage
                _isDisplayed = false;                                     //Collision, remove projectile
              }
            }
          }
        }
      }
    }
  }

  if (_coordinates.y < wave || _coordinates.y > 1 ||
      _coordinates.x < -1 || _coordinates.x > 1 ||
      _coordinates.z < -1 || _coordinates.z > 1) {
    _currentHealth = 0;
    _isDisplayed = false;
  }
}

void Projectile::draw() const {
  if (Game::getInstance().getShowLight()) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    GLfloat specular[] = {1.0f, 0.3f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    GLfloat diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    GLfloat shininess = 64.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  }

  glEnable(GL_BLEND);
  glPushMatrix();
  glTranslatef(_coordinates.x, _coordinates.y, _coordinates.z);
  Displayable::draw();
  glPopMatrix();
  glDisable(GL_BLEND);

  if (Game::getInstance().getShowLight()) {
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
}