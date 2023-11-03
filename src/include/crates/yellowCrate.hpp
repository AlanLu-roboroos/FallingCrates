#ifndef YELLOWCRATE_H
#define YELLOWCRATE_H

#include "crates/crate.hpp"
#include <memory>

class YellowCrate : public Crate {
public:
  YellowCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif