#include "crates/purpleCrate.hpp"

PurpleCrate::PurpleCrate() { init(); }

sf::Texture &PurpleCrate::getTexture() {
  return GameConstants::Textures::CRATE_PURPLE_TEXTURE;
}

bool PurpleCrate::explodable() { return true; }
bool PurpleCrate::moveable() { return true; }

std::shared_ptr<Crate> PurpleCrate::nextCrate() {
  std::shared_ptr<Crate> temp(new BlueCrate());
  return temp;
}