#include "crates/purpleCrate.hpp"

PurpleCrate::PurpleCrate() { init(); }

sf::Texture &PurpleCrate::getTexture() {
  return GameConstants::Textures::CRATE_PURPLE_TEXTURE;
}

bool PurpleCrate::explodable() { return true; }
bool PurpleCrate::moveable() { return state != CrateState::SPAWNING; }

Crate *PurpleCrate::nextCrate() {
  Crate *temp(new BlueCrate());
  return temp;
}