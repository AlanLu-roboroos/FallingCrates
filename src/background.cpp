#include "background.hpp"

bool Background::init() {
  if (!loadTextures())
    return 0;
  for (int i = 0; i < 8; i++) {
    platform_sprites[i] = sf::Sprite();
    platform_sprites[i].setTexture(PLATFORM_TEXTURE);
    platform_sprites[i].setScale(GameConstants::CRATE_SIZE.x / platform_sprites[i].getLocalBounds().width,
                                 GameConstants::CRATE_SIZE.y / platform_sprites[i].getLocalBounds().height);
    platform_sprites[i].setPosition(GameConstants::PLATFORM_POS[i]);
  }
  return 1;
}

bool Background::loadTextures() {
  return PLATFORM_TEXTURE.loadFromFile(GameConstants::PLATFORM_TEXTURE_PATH);
}

void Background::drawBackground(sf::RenderWindow &window) {
  for (sf::Sprite platform : platform_sprites)
    window.draw(platform);
}