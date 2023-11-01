#include "crates/crate.hpp"

Crate::Crate(int i_row, int i_column, int i_startHeight) {
  row = i_row;
  column = i_column;

  loadTextures();

  crate = sf::Sprite();
  crate.setTexture(crate_texture);
  crate.setScale(GameConstants::CRATE_SIZE.x / crate.getLocalBounds().width,
                 GameConstants::CRATE_SIZE.y / crate.getLocalBounds().height);
  crate.setOrigin(sf::Vector2f(8, 8));
}

bool Crate::loadTextures() {
  return !crate_texture.loadFromFile(GameConstants::CRATE_RED_TEXTURE_PATH);
}

void Crate::drawCrate(sf::RenderWindow &window) {
  crate.setPosition(sf::Vector2f(164, 596));
  window.draw(crate);
}