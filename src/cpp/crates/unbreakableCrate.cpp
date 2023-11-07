#include "crates/unbreakableCrate.hpp"

UnbreakableCrate::UnbreakableCrate() {
  init();
  crateType = GameConstants::CrateType::UNBREAKABLE_CRATE;
}

sf::Texture &UnbreakableCrate::getTexture() {
  return GameConstants::Resources::CRATE_UNBREAKABLE_TEXTURE;
}

bool UnbreakableCrate::explodable() { return false; }
bool UnbreakableCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType UnbreakableCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}