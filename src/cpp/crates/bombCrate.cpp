#include "crates/bombCrate.hpp"

BombCrate::BombCrate() {
  init();
  crateType = GameConstants::CrateType::BOMB_CRATE;
}

sf::Texture &BombCrate::getTexture() {
  return GameConstants::Resources::CRATE_BOMB_TEXTURE;
}

void BombCrate::drawCrate(sf::RenderWindow &window) {
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
        GameConstants::Resources::CRATE_BOMB_FLASHING_TEXTURE);
  } else {
    crateSprite.setTexture(GameConstants::Resources::CRATE_BOMB_TEXTURE);
  }
  window.draw(crateSprite);
}

bool BombCrate::isExploded() {
  if (bombClock.getElapsedTime().asMilliseconds() >
      GameConstants::BOMB_EXPLODE_TIME)
    return true;
  return false;
}

bool BombCrate::explodable() { return true; }
bool BombCrate::moveable() { return state != CrateState::SPAWNING; }

GameConstants::CrateType BombCrate::nextCrate() {
  return GameConstants::CrateType::MEGA_BOMB_CRATE;
}

void BombCrate::play() {
  bombClock.play();
  clock.play();
}

void BombCrate::pause() {
  bombClock.pause();
  clock.pause();
}