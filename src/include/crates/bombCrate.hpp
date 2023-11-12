#ifndef BOMBCRATE_H
#define BOMBCRATE_H

#include "clock.hpp"
#include "crates/crate.hpp"
#include <cmath>

class BombCrate : public Crate {
protected:
  Clock bombClock;

public:
  BombCrate();

  virtual sf::Texture &getTexture();
  virtual void drawCrate(sf::RenderWindow &window);
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
  virtual bool isExploded();
  void play();
  void pause();
};

#endif