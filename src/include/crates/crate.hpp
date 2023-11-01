#ifndef CRATE_H
#define CRATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"

class Crate {
private:
  bool infected;
  bool settled;

  sf::Sprite crate;

  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  virtual sf::Texture getTexture() = 0;

public:
  Crate();
  void drawCrate(sf::RenderWindow &window);
  void setSettled(bool _settled);
  sf::Vector2f getPos();

  virtual bool explodable() = 0;
  virtual bool moveable() = 0;
  virtual Crate &nextCrate() = 0;
};

#endif