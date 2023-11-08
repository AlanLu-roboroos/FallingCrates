#include "background.hpp"

Background::Background() {
  for (int i = 0; i < 8; i++) {
    m_platform_sprites[i] = sf::Sprite();
    m_platform_sprites[i].setTexture(
        GameConstants::Resources::PLATFORM_TEXTURE);
    m_platform_sprites[i].setScale(
        GameConstants::PLATFORM_SIZE.x /
            m_platform_sprites[i].getLocalBounds().width,
        GameConstants::PLATFORM_SIZE.y /
            m_platform_sprites[i].getLocalBounds().height);
    m_platform_sprites[i].setOrigin(sf::Vector2f(11, 11));
    m_platform_sprites[i].setPosition(GameConstants::PLATFORM_POS[i]);

    m_spawn_sprites[i] = sf::Sprite();
    m_spawn_sprites[i].setTexture(GameConstants::Resources::SPAWN_TEXTURE);
    m_spawn_sprites[i].setScale(GameConstants::SPAWN_SIZE.x /
                                    m_spawn_sprites[i].getLocalBounds().width,
                                GameConstants::SPAWN_SIZE.y /
                                    m_spawn_sprites[i].getLocalBounds().height);
    m_spawn_sprites[i].setOrigin(sf::Vector2f(11, 11));
    m_spawn_sprites[i].setPosition(GameConstants::SPAWN_POS[i]);
  }
  m_borderLine = sf::RectangleShape(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::BORDER_WIDTH));
  m_borderLine.setFillColor(GameConstants::BORDER_COLOR);
  m_borderLine.setPosition(0, GameConstants::BORDER_HEIGHT);

  m_header = sf::RectangleShape(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::BORDER_HEIGHT));
  m_header.setFillColor(GameConstants::HEADER_COLOR);

  for (int i = 0; i < 3; i++) {
    sf::RectangleShape temp;
    temp.setFillColor(GameConstants::ITEM_BACKGROUND_COLOR);
    temp.setSize(GameConstants::ITEMS_BACKGROUND_SIZE);
    temp.setOrigin(sf::Vector2f(temp.getLocalBounds().width / 2,
                                temp.getLocalBounds().height / 2));
    temp.setPosition(GameConstants::ITEMS_POS[i]);
    m_items.push_back(temp);
  }
}

void Background::drawBackground(sf::RenderWindow &window) {
  for (sf::Sprite platform : m_platform_sprites)
    window.draw(platform);
  for (sf::Sprite spawn : m_spawn_sprites)
    window.draw(spawn);
  window.draw(m_header);
  window.draw(m_borderLine);
  for (auto item : m_items)
    window.draw(item);
}