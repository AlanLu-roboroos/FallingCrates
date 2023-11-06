#include "crates/crate.hpp"

void Crate::init() {
  crateSprite = sf::Sprite();
  crateSprite.setTexture(getTexture());
  crateSprite.setScale(
      GameConstants::CRATE_SIZE.x / crateSprite.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / crateSprite.getLocalBounds().height);
  crateSprite.setPosition(sf::Vector2f(-1000, -1000));
  crateSprite.setOrigin(sf::Vector2f(8, 8));
  state = Crate::NONE;
}

bool Crate::isExploded() { return false; }

void Crate::drawCrate(sf::RenderWindow &window) { window.draw(crateSprite); }

void Crate::setPosition(sf::Vector2f pos) { crateSprite.setPosition(pos); }
void Crate::setPosition(int x, int y) { setPosition(sf::Vector2f(x, y)); }

void Crate::setSize(sf::Vector2f size) {
  crateSprite.setScale(size.x / crateSprite.getLocalBounds().width,
                       size.y / crateSprite.getLocalBounds().height);
}

void Crate::setAlpha(int alpha) {
  crateSprite.setColor(sf::Color(255, 255, 255, alpha));
}

void Crate::setState(Crate::CrateState _state) { state = _state; }

sf::Vector2f Crate::getPos() { return crateSprite.getPosition(); }

Crate::CrateState Crate::getState() { return state; }

void Crate::restartClock() { clock.restart(); }
sf::Time Crate::getElapsedTime() { return clock.getElapsedTime(); }

void Crate::setInitHeight(int height) { initHeight = height; }
float Crate::getInitHeight() { return initHeight; }

GameConstants::CrateType Crate::getCrateType() { return crateType; }