#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "SFML/Graphics.hpp"

class Clock {
private:
  sf::Clock m_clock;
  float m_factor;

public:
  Clock();
  sf::Time getElapsedTime();
  float getMilliSeconds();
  void restart();
  void setTimeSpeed(float _factor);
};

#endif