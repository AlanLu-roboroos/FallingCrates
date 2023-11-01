#ifndef CRATE_H
#define CRATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"

class Crate {
private:
  int row, column, x, y;
  bool infected;
  bool explodable;
  float fallStartTime;

  sf::Sprite crate;

public:
  Crate(int i_row, int i_column, int startHeight);
  void drawCrate(sf::RenderWindow &window);
};

#endif