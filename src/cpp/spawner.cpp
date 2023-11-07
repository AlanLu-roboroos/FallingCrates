#include "spawner.hpp"

Spawner::Spawner() {
  clock.restart();
  lastTime = 0;
}

GameConstants::CrateType Spawner::update() {
  if (clock.getElapsedTime().asMilliseconds() - lastTime > 2000) {
    lastTime = clock.getElapsedTime().asMilliseconds();
    return GameConstants::CrateType::PURPLE_CRATE;
  }
  return GameConstants::CrateType::NONE;
}