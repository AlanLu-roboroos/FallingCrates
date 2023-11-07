#include "crates/heavyCrate.hpp"

HeavyCrate::HeavyCrate() {
  init();
  crateType = GameConstants::CrateType::HEAVY_CRATE;
}

sf::Texture &HeavyCrate::getTexture() {
  return GameConstants::Resources::CRATE_HEAVY_TEXTURE;
}

bool HeavyCrate::explodable() { return true; }
bool HeavyCrate::moveable() { return false; }

GameConstants::CrateType HeavyCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}