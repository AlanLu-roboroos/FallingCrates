#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include <vector>

class Background {
  private:
  sf::Texture PLATFORM_TEXTURE;
  sf::Sprite platform_sprites[8];
  bool loadTextures();

  public:
  bool init();
  void drawBackground(sf::RenderWindow &window);
};

#endif