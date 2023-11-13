#include "crates/virusCrate.hpp"

VirusCrate::VirusCrate() {
  init();
  infected = true;
  crateType = GameConstants::CrateType::VIRUS_CRATE;
}

sf::Texture &VirusCrate::getTexture() {
  return GameConstants::Resources::CRATE_VIRUS_TEXTURE;
}

bool VirusCrate::explodable() { return true; }
bool VirusCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType VirusCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}