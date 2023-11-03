#ifndef REDCRATE_H
#define REDCRATE_H

#include "crates/crate.hpp"
#include <memory>

class RedCrate : public Crate {
public:
  RedCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif