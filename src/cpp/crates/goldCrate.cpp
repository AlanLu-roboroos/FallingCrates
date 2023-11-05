#include "crates/goldCrate.hpp"

GoldCrate::GoldCrate() {
  init();
  crateType = GameConstants::CrateType::GOLD_CRATE;
}

sf::Texture &GoldCrate::getTexture() {
  return GameConstants::Resources::CRATE_GOLD_TEXTURE;
}

bool GoldCrate::explodable() { return true; }
bool GoldCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType GoldCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}