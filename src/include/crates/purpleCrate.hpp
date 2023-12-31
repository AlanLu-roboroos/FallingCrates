#ifndef PURPLECRATE_H
#define PURPLECRATE_H

#include "crates/crate.hpp"
#include <memory>

class PurpleCrate : public Crate {
public:
  PurpleCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif