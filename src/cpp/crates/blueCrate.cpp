#include "crates/blueCrate.hpp"

BlueCrate::BlueCrate() {
  init();
  crateType = GameConstants::CrateType::BLUE_CRATE;
}

sf::Texture &BlueCrate::getTexture() {
  return GameConstants::Textures::CRATE_BLUE_TEXTURE;
}

bool BlueCrate::explodable() { return true; }
bool BlueCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType BlueCrate::nextCrate() {
  return GameConstants::CrateType::GREEN_CRATE;
}