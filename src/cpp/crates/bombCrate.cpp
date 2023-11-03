#include "crates/bombCrate.hpp"

BombCrate::BombCrate() {
  init();
  crateType = GameConstants::CrateType::BOMB_CRATE;
}

sf::Texture &BombCrate::getTexture() {
  return GameConstants::Textures::CRATE_BOMB_TEXTURE;
}

bool BombCrate::explodable() { return true; }
bool BombCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType BombCrate::nextCrate() {
  return GameConstants::CrateType::GREEN_CRATE;
}