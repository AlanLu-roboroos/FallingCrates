#include "clock.hpp"

float Clock::m_factor = 1;

Clock::Clock() { m_clock = sf::Clock(); }

sf::Time Clock::getElapsedTime() {
  return sf::microseconds(m_clock.getElapsedTime().asMicroseconds() * m_factor +
                          m_time.asMicroseconds());
}

float Clock::getMilliSeconds() {
  return m_clock.getElapsedTime().asMilliseconds() * m_factor +
         m_time.asMilliseconds();
}

void Clock::restart() {
  m_clock.restart();
  m_time = sf::microseconds(0);
}

void Clock::setFactor(float _factor) {
  Clock::m_factor = _factor;
  m_time = m_clock.getElapsedTime();
  m_clock.restart();
}