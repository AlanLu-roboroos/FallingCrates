#ifndef BOMBCRATE_H
#define BOMBCRATE_H

#include "crates/crate.hpp"

class BombCrate : public Crate {
public:
  BombCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif