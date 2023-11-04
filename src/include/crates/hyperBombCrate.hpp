#ifndef HYPERBOMBCRATE_H
#define HYPERBOMBCRATE_H

#include "crates/bombCrate.hpp"
#include <cmath>

class HyperBombCrate : public BombCrate {
public:
  HyperBombCrate();

  virtual sf::Texture &getTexture();
  virtual void drawCrate(sf::RenderWindow &window);
  virtual GameConstants::CrateType nextCrate();
};

#endif