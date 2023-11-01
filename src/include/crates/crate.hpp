#ifndef CRATE_H
#define CRATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include <memory>

class Crate {
private:
  bool infected;
  bool settled;

  sf::Sprite crate;

  virtual sf::Texture &getTexture() = 0;

protected:
  void init();

public:
  void drawCrate(sf::RenderWindow &window);
  void setSettled(bool _settled);
  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  sf::Vector2f getPos();

  virtual bool explodable() = 0;
  virtual bool moveable() = 0;
  virtual std::shared_ptr<Crate> nextCrate() = 0;
};

#endif