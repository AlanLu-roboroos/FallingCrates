#include "crates/yellowCrate.hpp"

YellowCrate::YellowCrate() {
  init();
  crateType = GameConstants::CrateType::YELLOW_CRATE;
}

sf::Texture &YellowCrate::getTexture() {
  return GameConstants::Textures::CRATE_YELLOW_TEXTURE;
}

bool YellowCrate::explodable() { return true; }
bool YellowCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType YellowCrate::nextCrate() {
  return GameConstants::CrateType::ORANGE_CRATE;
}