#ifndef ORANGECRATE_H
#define ORANGECRATE_H

#include "crates/crate.hpp"
#include <memory>

class OrangeCrate : public Crate {
public:
  OrangeCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif