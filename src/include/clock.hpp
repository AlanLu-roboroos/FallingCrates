#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "SFML/Graphics.hpp"

class Clock {
private:
  sf::Clock m_clock;

public:
  static float m_factor;
  Clock();
  sf::Time getElapsedTime();
  float getMilliSeconds();
  void restart();
};

#endif