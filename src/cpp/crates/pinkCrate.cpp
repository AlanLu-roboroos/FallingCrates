#include "crates/pinkCrate.hpp"

PinkCrate::PinkCrate() {
  init();
  crateType = GameConstants::CrateType::PINK_CRATE;
}

sf::Texture &PinkCrate::getTexture() {
  return GameConstants::Resources::CRATE_PINK_TEXTURE;
}

bool PinkCrate::explodable() { return true; }
bool PinkCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType PinkCrate::nextCrate() {
  return GameConstants::CrateType::GOLD_CRATE;
}