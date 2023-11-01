#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include <vector>

class Background {
private:
  sf::Sprite platform_sprites[8];
  sf::Sprite spawn_sprites[8];

  sf::RectangleShape borderLine;
  sf::RectangleShape header;

public:
  Background();
  void drawBackground(sf::RenderWindow &window);
};

#endif