#ifndef GREENCRATE_H
#define GREENCRATE_H

#include "crates/crate.hpp"
#include <memory>

class GreenCrate : public Crate {
public:
  GreenCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual GameConstants::CrateType nextCrate();
};

#endif