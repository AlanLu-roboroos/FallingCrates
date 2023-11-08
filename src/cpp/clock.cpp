#include "clock.hpp"

float Clock::m_factor = 1;

Clock::Clock() { m_clock = sf::Clock(); }

sf::Time Clock::getElapsedTime() {
  return sf::microseconds(m_clock.getElapsedTime().asMicroseconds() * m_factor);
}

float Clock::getMilliSeconds() {
  return m_clock.getElapsedTime().asMilliseconds() * m_factor;
}

void Clock::restart() { m_clock.restart(); }
