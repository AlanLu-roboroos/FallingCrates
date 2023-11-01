#ifndef GRABBER_H
#define GRABBER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "crates.hpp"

class Grabber {
private:
  int column;
  float x, y;

  sf::Sprite grabHori;
  sf::Sprite grabLeft;
  sf::Sprite grabRight;
  sf::Sprite grabVert;

  // sf::CircleShape _centreDot;
  // sf::RectangleShape _vertBoundingBox;

  enum GrabberState {
    STARTING,     // State when game starts
    EMPTY,        // Has no crate and is idling
    FULL,         // Has a crate and is idling
    GRABBING,     // When grabber is lowering to grab a crate
    PLACING,      // When grabber is lowering to place a crate
    LIFTINGCRATE, // When grabber is lifting with a crate
    RETURNING     // Wheh grabber is lifting with no crate
  };

  GrabberState state;

  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  void openGripper();
  void closeGripper();

public:
  bool init();
  void update();
  void goTo(int column, Crates crates);
  void drawGrabber(sf::RenderWindow &window);
};

#endif