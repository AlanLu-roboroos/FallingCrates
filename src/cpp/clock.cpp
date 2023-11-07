#include "clock.hpp"

Clock::Clock() {
  clock = sf::Clock();
  factor = 1;
}

sf::Time Clock::getElapsedTime() {
  return sf::microseconds(clock.getElapsedTime().asMicroseconds() * factor);
}

float Clock::getMilliSeconds() {
  return clock.getElapsedTime().asMilliseconds() * factor;
}

void Clock::restart() { clock.restart(); }

void Clock::setTimeSpeed(float _factor) { factor = _factor; }