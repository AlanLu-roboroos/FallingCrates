#ifndef VIRUSCRATE_H
#define VIRUSCRATE_H

#include "crates/crate.hpp"

class VirusCrate : public Crate {
public:
  VirusCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif