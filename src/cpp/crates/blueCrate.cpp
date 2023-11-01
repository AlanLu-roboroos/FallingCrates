#include "crates/blueCrate.hpp"

BlueCrate::BlueCrate() { init(); }

sf::Texture &BlueCrate::getTexture() {
  return GameConstants::Textures::CRATE_BLUE_TEXTURE;
}

bool BlueCrate::explodable() { return true; }
bool BlueCrate::moveable() { return true; }

std::shared_ptr<Crate> BlueCrate::nextCrate() {
  std::shared_ptr<Crate> temp(nullptr);
  return temp;
}