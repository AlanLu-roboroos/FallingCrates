#include "clock.hpp"

float Clock::m_factor = 1;

Clock::Clock() {
  m_clock = sf::Clock();
  lastPaused = false;
  paused = false;
}

sf::Time Clock::getElapsedTime() {
  if (paused)
    return m_time;
  else
    return sf::microseconds(m_clock.getElapsedTime().asMicroseconds() *
                                m_factor +
                            m_time.asMicroseconds());
}

float Clock::getMilliSeconds() {
  if (paused)
    return m_time.asMilliseconds();
  else
    return m_clock.getElapsedTime().asMilliseconds() * m_factor +
           m_time.asMilliseconds();
}

void Clock::restart() {
  m_clock.restart();
  m_time = sf::microseconds(0);
}

void Clock::setFactor(float _factor) {
  Clock::m_factor = _factor;
  if (paused)
    m_time += m_clock.getElapsedTime();
  else
    m_time = m_clock.getElapsedTime();
  m_clock.restart();
}

void Clock::pause() {
  if (paused)
    return;
  paused = true;
  m_time += m_clock.getElapsedTime();
}

void Clock::play() {
  if (!paused)
    return;
  paused = false;
  m_clock.restart();
}