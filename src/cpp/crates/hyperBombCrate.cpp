#include "crates/hyperBombCrate.hpp"

HyperBombCrate::HyperBombCrate() {
  init();
  crateType = GameConstants::CrateType::HYPER_BOMB_CRATE;
}

sf::Texture &HyperBombCrate::getTexture() {
  return GameConstants::Resources::CRATE_HYPER_BOMB_TEXTURE;
}

void HyperBombCrate::drawCrate(sf::RenderWindow &window) {
  if (static_cast<int>(bombClock.getElapsedTime().asMilliseconds()) %
          static_cast<int>(GameConstants::BOMB_FLASHING_TIME * 2) >
      GameConstants::BOMB_FLASHING_TIME) {
    crateSprite.setTexture(
        GameConstants::Resources::CRATE_HYPER_BOMB_FLASHING_TEXTURE);
  } else {
    crateSprite.setTexture(GameConstants::Resources::CRATE_HYPER_BOMB_TEXTURE);
  }
  window.draw(crateSprite);
}

GameConstants::CrateType HyperBombCrate::nextCrate() {
  return GameConstants::CrateType::NONE;
}