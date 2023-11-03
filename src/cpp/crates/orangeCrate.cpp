#include "crates/orangeCrate.hpp"

OrangeCrate::OrangeCrate() {
  init();
  crateType = GameConstants::CrateType::ORANGE_CRATE;
}

sf::Texture &OrangeCrate::getTexture() {
  return GameConstants::Textures::CRATE_ORANGE_TEXTURE;
}

bool OrangeCrate::explodable() { return true; }
bool OrangeCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType OrangeCrate::nextCrate() {
  return GameConstants::CrateType::RED_CRATE;
}