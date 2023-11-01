#ifndef BLUECRATE_H
#define BLUECRATE_H

#include "crates/crate.hpp"
#include <memory>

class BlueCrate : public Crate {
public:
  BlueCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual Crate *nextCrate();
};

#endif