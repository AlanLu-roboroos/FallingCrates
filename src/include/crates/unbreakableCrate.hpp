#ifndef UNBREAKABLECRATE_H
#define UNBREAKABLECRATE_H

#include "crates/crate.hpp"

class UnbreakableCrate : public Crate {
public:
  UnbreakableCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif