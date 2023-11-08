#include "crates/multiColorCrate.hpp"

MultiColorCrate::MultiColorCrate() {
  init();
  crateType = GameConstants::CrateType::MULTICOLOR_CRATE;
}

sf::Texture &MultiColorCrate::getTexture() {
  return GameConstants::Resources::CRATE_MULTICOLOR_TEXTURE;
}

bool MultiColorCrate::explodable() { return true; }
bool MultiColorCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType MultiColorCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}