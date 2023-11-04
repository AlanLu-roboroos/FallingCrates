#ifndef MEGABOMBCRATE_H
#define MEGABOMBCRATE_H

#include "crates/bombCrate.hpp"
#include <cmath>

class MegaBombCrate : public BombCrate {
public:
  MegaBombCrate();

  virtual sf::Texture &getTexture();
  virtual void drawCrate(sf::RenderWindow &window);
  virtual GameConstants::CrateType nextCrate();
};

#endif