#include "crates/crate.hpp"

void Crate::init() {
  crate = sf::Sprite();
  crate.setTexture(getTexture());
  crate.setScale(GameConstants::CRATE_SIZE.x / crate.getLocalBounds().width,
                 GameConstants::CRATE_SIZE.y / crate.getLocalBounds().height);
  crate.setOrigin(sf::Vector2f(8, 8));
}

void Crate::drawCrate(sf::RenderWindow &window) { window.draw(crate); }

void Crate::setPosition(sf::Vector2f pos) { crate.setPosition(pos); }
void Crate::setPosition(int x, int y) { setPosition(sf::Vector2f(x, y)); }

void Crate::setSettled(bool _settled) { settled = _settled; }

sf::Vector2f Crate::getPos() { return crate.getPosition(); }