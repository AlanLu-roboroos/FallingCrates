#ifndef MULTICOLORCRATE_H
#define MULTICOLORCRATE_H

#include "crates/crate.hpp"

class MultiColorCrate : public Crate {
public:
  MultiColorCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif