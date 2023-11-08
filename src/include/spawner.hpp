#ifndef SPAWNER_H
#define SPAWNER_H

#include "SFML/Graphics.hpp"
#include "clock.hpp"
#include "constants.hpp"

class Spawner {
private:
  Clock m_clock;
  float m_lastTime;

public:
  Spawner();
  GameConstants::CrateType update();
};

#endif