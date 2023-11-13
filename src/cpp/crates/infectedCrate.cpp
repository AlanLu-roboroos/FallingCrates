#include "crates/infectedCrate.hpp"

InfectedCrate::InfectedCrate() {
  init();
  infected = true;
  crateType = GameConstants::CrateType::INFECTED_CRATE;
}

sf::Texture &InfectedCrate::getTexture() {
  return GameConstants::Resources::CRATE_VIRUS_TEXTURE;
}

bool InfectedCrate::explodable() { return true; }
bool InfectedCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType InfectedCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}