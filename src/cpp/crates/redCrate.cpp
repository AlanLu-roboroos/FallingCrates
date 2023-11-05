#include "crates/redCrate.hpp"

RedCrate::RedCrate() {
  init();
  crateType = GameConstants::CrateType::RED_CRATE;
}

sf::Texture &RedCrate::getTexture() {
  return GameConstants::Resources::CRATE_RED_TEXTURE;
}

bool RedCrate::explodable() { return true; }
bool RedCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType RedCrate::nextCrate() {
  return GameConstants::CrateType::PINK_CRATE;
}