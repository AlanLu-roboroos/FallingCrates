#include "spawner.hpp"

Spawner::Spawner() {
  m_clock.restart();
  m_lastTime = 0;
}

GameConstants::CrateType Spawner::update() {
  if (m_clock.getMilliSeconds() - m_lastTime > 2000) {
    m_lastTime = m_clock.getElapsedTime().asMilliseconds();
    return GameConstants::CrateType::PURPLE_CRATE;
  }
  return GameConstants::CrateType::NONE;
}

void Spawner::setClockFactor(float _factor) { m_clock.setFactor(_factor); }