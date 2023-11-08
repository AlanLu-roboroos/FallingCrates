#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include <vector>

class Background {
private:
  sf::Sprite m_platform_sprites[8];
  sf::Sprite m_spawn_sprites[8];

  sf::RectangleShape m_borderLine;
  sf::RectangleShape m_header;

public:
  Background();
  void drawBackground(sf::RenderWindow &window);
};

#endif