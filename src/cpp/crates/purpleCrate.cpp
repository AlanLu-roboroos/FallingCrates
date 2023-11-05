#include "crates/purpleCrate.hpp"

PurpleCrate::PurpleCrate() {
  init();
  crateType = GameConstants::CrateType::PURPLE_CRATE;
}

sf::Texture &PurpleCrate::getTexture() {
  return GameConstants::Resources::CRATE_PURPLE_TEXTURE;
}

bool PurpleCrate::explodable() { return true; }
bool PurpleCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType PurpleCrate::nextCrate() {
  return GameConstants::CrateType::BLUE_CRATE;
}