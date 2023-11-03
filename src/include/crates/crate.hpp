#ifndef CRATE_H
#define CRATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include <memory>

class Crate {
public:
  enum CrateState { NONE, SPAWNING, FALLING, IDLE };

protected:
  bool infected;

  CrateState state;
  sf::Clock clock;

  float initHeight;

  sf::Sprite crateSprite;

  virtual sf::Texture &getTexture() = 0;

  void init();

public:
  void drawCrate(sf::RenderWindow &window);
  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  void setSize(sf::Vector2f size);
  sf::Vector2f getPos();
  CrateState getState();
  void setState(CrateState _state);
  void restartClock();
  sf::Time getElapsedTime();

  void setInitHeight(int height);
  float getInitHeight();

  virtual ~Crate() = default;
  virtual bool explodable() = 0;
  virtual bool moveable() = 0;
  virtual Crate *nextCrate() = 0;
};

#endif