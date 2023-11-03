#ifndef GOLDCRATE_H
#define GOLDCRATE_H

#include "crates/crate.hpp"
#include <memory>

class GoldCrate : public Crate {
public:
  GoldCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif