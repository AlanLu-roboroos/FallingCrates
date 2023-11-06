#include "crates/megaBombCrate.hpp"

MegaBombCrate::MegaBombCrate() {
  init();
  crateType = GameConstants::CrateType::MEGA_BOMB_CRATE;
}

sf::Texture &MegaBombCrate::getTexture() {
  return GameConstants::Resources::CRATE_MEGA_BOMB_TEXTURE;
}

void MegaBombCrate::drawCrate(sf::RenderWindow &window) {
  if (static_cast<int>(bombClock.getElapsedTime().asMilliseconds()) %
          static_cast<int>((GameConstants::BOMB_FLASHING_TIME -
                            ((GameConstants::BOMB_FLASHING_TIME - 150) /
                             GameConstants::BOMB_EXPLODE_TIME) *
                                getElapsedTime().asMilliseconds()) *
                           2) >
      GameConstants::BOMB_FLASHING_TIME -
          ((GameConstants::BOMB_FLASHING_TIME - 150) /
           GameConstants::BOMB_EXPLODE_TIME) *
              getElapsedTime().asMilliseconds()) {
    crateSprite.setTexture(
        GameConstants::Resources::CRATE_MEGA_BOMB_FLASHING_TEXTURE);
  } else {
    crateSprite.setTexture(GameConstants::Resources::CRATE_MEGA_BOMB_TEXTURE);
  }
  window.draw(crateSprite);
}

GameConstants::CrateType MegaBombCrate::nextCrate() {
  return GameConstants::CrateType::HYPER_BOMB_CRATE;
}