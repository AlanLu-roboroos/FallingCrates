#include "crates/megaBombCrate.hpp"

MegaBombCrate::MegaBombCrate() {
  init();
  crateType = GameConstants::CrateType::MEGA_BOMB_CRATE;
}

sf::Texture &MegaBombCrate::getTexture() {
  return GameConstants::Textures::CRATE_MEGA_BOMB_TEXTURE;
}

void MegaBombCrate::drawCrate(sf::RenderWindow &window) {
  if (static_cast<int>(bombClock.getElapsedTime().asMilliseconds()) %
          static_cast<int>(GameConstants::BOMB_FLASHING_TIME * 2) >
      GameConstants::BOMB_FLASHING_TIME) {
    crateSprite.setTexture(
        GameConstants::Textures::CRATE_MEGA_BOMB_FLASHING_TEXTURE);
  } else {
    crateSprite.setTexture(GameConstants::Textures::CRATE_MEGA_BOMB_TEXTURE);
  }
  window.draw(crateSprite);
}

GameConstants::CrateType MegaBombCrate::nextCrate() {
  return GameConstants::CrateType::HYPER_BOMB_CRATE;
}