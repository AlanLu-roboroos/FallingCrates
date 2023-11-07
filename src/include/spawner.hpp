#ifndef SPAWNER_H
#define SPAWNER_H

#include "SFML/Graphics.hpp"
#include "clock.hpp"
#include "constants.hpp"

class Spawner {
private:
  Clock clock;
  float lastTime;

public:
  Spawner();
  GameConstants::CrateType update();
};

#endif