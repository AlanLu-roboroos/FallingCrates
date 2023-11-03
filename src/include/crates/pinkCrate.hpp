#ifndef PINKCRATE_H
#define PINKCRATE_H

#include "crates/crate.hpp"
#include <memory>

class PinkCrate : public Crate {
public:
  PinkCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif