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

    spawn_sprites[i] = sf::Sprite();
    spawn_sprites[i].setTexture(SPAWN_TEXTURE);
    spawn_sprites[i].setScale(GameConstants::CRATE_SIZE.x / spawn_sprites[i].getLocalBounds().width,
                              GameConstants::CRATE_SIZE.y / spawn_sprites[i].getLocalBounds().height);
    spawn_sprites[i].setPosition(GameConstants::SPAWN_POS[i]);
  }
  borderLine = sf::RectangleShape(sf::Vector2f(1924, 10));
  borderLine.setFillColor(sf::Color(50, 50, 50));
  borderLine.setPosition(0, 146);

  header = sf::RectangleShape(sf::Vector2f(1924, 146));
  header.setFillColor(sf::Color(120, 120, 120));
  return 1;
}

bool Background::loadTextures() {
  bool loaded = true;
  loaded &= PLATFORM_TEXTURE.loadFromFile(GameConstants::PLATFORM_TEXTURE_PATH);
  loaded &= SPAWN_TEXTURE.loadFromFile(GameConstants::SPAWN_TEXTURE_PATH);
  return loaded;
}

void Background::drawBackground(sf::RenderWindow &window) {
  for (sf::Sprite platform : platform_sprites)
    window.draw(platform);
  for (sf::Sprite spawn : spawn_sprites)
    window.draw(spawn);
  window.draw(header);
  window.draw(borderLine);
}