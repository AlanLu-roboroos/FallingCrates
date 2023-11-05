#include "crates/greenCrate.hpp"

GreenCrate::GreenCrate() {
  init();
  crateType = GameConstants::CrateType::GREEN_CRATE;
}

sf::Texture &GreenCrate::getTexture() {
  return GameConstants::Resources::CRATE_GREEN_TEXTURE;
}

bool GreenCrate::explodable() { return true; }
bool GreenCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType GreenCrate::nextCrate() {
  return GameConstants::CrateType::YELLOW_CRATE;
}