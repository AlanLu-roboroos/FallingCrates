#ifndef CRATE_H
#define CRATE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "clock.hpp"
#include "constants.hpp"

class Crate {
public:
  enum CrateState { NONE, SPAWNING, FALLING, IDLE, FADINGOUT, FADINGIN };

protected:
  bool infected;

  CrateState state;
  Clock clock;
  GameConstants::CrateType crateType;

  float initHeight;

  sf::Sprite crateSprite;

  virtual sf::Texture &getTexture() = 0;

  void init();

public:
  virtual void drawCrate(sf::RenderWindow &window);
  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  void setSize(sf::Vector2f size);
  void setAlpha(int alpha);
  sf::Vector2f getPos();
  CrateState getState();
  void setState(CrateState _state);
  void restartClock();
  sf::Time getElapsedTime();

  void setInitHeight(int height);
  float getInitHeight();

  GameConstants::CrateType getCrateType();

  virtual ~Crate() = default;
  virtual bool isExploded();
  virtual bool explodable() = 0;
  virtual bool moveable() = 0;
  virtual GameConstants::CrateType nextCrate() = 0;
};

#endif