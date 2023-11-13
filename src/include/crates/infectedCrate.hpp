#ifndef INFECTEDCRATE_H
#define INFECTEDCRATE_H

#include "crates/crate.hpp"

class InfectedCrate : public Crate {
public:
  InfectedCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif