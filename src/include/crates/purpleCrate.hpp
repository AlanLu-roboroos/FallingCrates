#ifndef PURPLECRATE_H
#define PURPLECRATE_H

#include "crates/blueCrate.hpp"
#include "crates/crate.hpp"
#include <memory>

class PurpleCrate : public Crate {
public:
  PurpleCrate();

  virtual sf::Texture &getTexture();
  virtual bool explodable();
  virtual bool moveable();
  virtual std::shared_ptr<Crate> nextCrate();
};

#endif