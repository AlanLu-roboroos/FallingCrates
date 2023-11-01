#include "crates/crate.hpp"

void Crate::init() {
  crateSprite = sf::Sprite();
  crateSprite.setTexture(getTexture());
  crateSprite.setScale(
      GameConstants::CRATE_SIZE.x / crateSprite.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / crateSprite.getLocalBounds().height);
  crateSprite.setOrigin(sf::Vector2f(8, 8));
}

void Crate::drawCrate(sf::RenderWindow &window) { window.draw(crateSprite); }

void Crate::setPosition(sf::Vector2f pos) { crateSprite.setPosition(pos); }
void Crate::setPosition(int x, int y) { setPosition(sf::Vector2f(x, y)); }

void Crate::setSettled(bool _settled) { settled = _settled; }

sf::Vector2f Crate::getPos() { return crateSprite.getPosition(); }