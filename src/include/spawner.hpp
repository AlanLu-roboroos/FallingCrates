#ifndef SPAWNER_H
#define SPAWNER_H

#include "SFML/Graphics.hpp"
#include "constants.hpp"

class Spawner {
private:
  sf::Clock clock;
  float lastTime;

public:
  Spawner();
  GameConstants::CrateType update();
};

#endif