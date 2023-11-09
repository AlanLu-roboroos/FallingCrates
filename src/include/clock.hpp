#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "SFML/Graphics.hpp"

class Clock {
private:
  sf::Clock m_clock;
  sf::Time m_time;
  static float m_factor;

public:
  Clock();
  sf::Time getElapsedTime();
  float getMilliSeconds();
  void restart();
  void setFactor(float _factor);
};

#endif