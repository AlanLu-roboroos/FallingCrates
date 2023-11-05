#include "background.hpp"

Background::Background() {
  for (int i = 0; i < 8; i++) {
    platform_sprites[i] = sf::Sprite();
    platform_sprites[i].setTexture(GameConstants::Resources::PLATFORM_TEXTURE);
    platform_sprites[i].setScale(
        GameConstants::PLATFORM_SIZE.x /
            platform_sprites[i].getLocalBounds().width,
        GameConstants::PLATFORM_SIZE.y /
            platform_sprites[i].getLocalBounds().height);
    platform_sprites[i].setOrigin(sf::Vector2f(11, 11));
    platform_sprites[i].setPosition(GameConstants::PLATFORM_POS[i]);

    spawn_sprites[i] = sf::Sprite();
    spawn_sprites[i].setTexture(GameConstants::Resources::SPAWN_TEXTURE);
    spawn_sprites[i].setScale(
        GameConstants::SPAWN_SIZE.x / spawn_sprites[i].getLocalBounds().width,
        GameConstants::SPAWN_SIZE.y / spawn_sprites[i].getLocalBounds().height);
    spawn_sprites[i].setOrigin(sf::Vector2f(11, 11));
    spawn_sprites[i].setPosition(GameConstants::SPAWN_POS[i]);
  }
  borderLine = sf::RectangleShape(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::BORDER_WIDTH));
  borderLine.setFillColor(GameConstants::BORDER_COLOR);
  borderLine.setPosition(0, GameConstants::BORDER_HEIGHT);

  header = sf::RectangleShape(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::BORDER_HEIGHT));
  header.setFillColor(GameConstants::HEADER_COLOR);
}

void Background::drawBackground(sf::RenderWindow &window) {
  for (sf::Sprite platform : platform_sprites)
    window.draw(platform);
  for (sf::Sprite spawn : spawn_sprites)
    window.draw(spawn);
  window.draw(header);
  window.draw(borderLine);
}