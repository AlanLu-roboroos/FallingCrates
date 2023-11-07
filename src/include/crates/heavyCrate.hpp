#ifndef HEAVYCRATE_H
#define HEAVYCRATE_H

#include "crates/crate.hpp"

class HeavyCrate : public Crate {
public:
  HeavyCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif