#ifndef GRABBER_H
#define GRABBER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "crates.hpp"

class Grabber {
private:
  float column;
  float x, y;

  sf::Sprite grabHori;
  sf::Sprite grabLeft;
  sf::Sprite grabRight;
  sf::Sprite grabVert;

  sf::Clock clock;
  sf::Time lastTime;

  // sf::CircleShape _centreDot;
  // sf::RectangleShape _vertBoundingBox;

  enum GrabberState {
    STARTING,     // State when game starts
    EMPTY,        // Has no crate and is idling
    FULL,         // Has a crate and is idling
    SLIDINGLEFT,  // Moving to column
    SLIDINGRIGHT, // Moving to column
    GRABBING,     // When grabber is lowering to grab a crate
    PLACING,      // When grabber is lowering to place a crate
    LIFTINGCRATE, // When grabber is lifting with a crate
    RETURNING     // Wheh grabber is lifting with no crate
  };

  GrabberState state;
  GrabberState nextState;

  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  void move(sf::Vector2f delta);
  void move(int x, int y);
  sf::Vector2f getPosition();
  void openGripper();
  void closeGripper();

public:
  Grabber();
  void update(Crates &_crates);
  void goTo(int column, Crates &_crates);
  void drawGrabber(sf::RenderWindow &window);
  int getColumn();
  bool isActive();
};

#endif