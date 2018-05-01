//
//  main.cpp
//  IslandDefense3D
//
//  Created by Mathieu Corti on 5/01/18.
//

#include <cstdlib>

#include "srcs/includes/Game.hpp"

int main(int argc, char **argv) {
  Game::getInstance().start(argc, argv);
  return EXIT_SUCCESS;
}