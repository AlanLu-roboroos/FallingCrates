#ifndef GRABBER_H
#define GRABBER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include "crates.hpp"

class Grabber {
private:
  float m_column;

  sf::Sprite m_grabHori;
  sf::Sprite m_grabLeft;
  sf::Sprite m_grabRight;
  sf::Sprite m_grabVert;

  Clock m_clock;
  sf::Time m_lastTime;

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
    RETURNING,    // Wheh grabber is lifting with no crate
    NONE          // TESTING
  };

  GrabberState m_state;
  GrabberState m_nextState;

  Crates *m_crates;
  std::vector<int> m_gotoQueue;

  void setPosition(sf::Vector2f pos);
  void setPosition(int x, int y);
  void move(sf::Vector2f delta);
  void move(int x, int y);
  sf::Vector2f getPosition();
  void openGripper();
  void closeGripper();

public:
  Grabber(Crates *_crates);
  void update();
  void goTo(int column);
  void queueGoTo(int column);
  void drawGrabber(sf::RenderWindow &window);
  int getColumn();
  bool isActive();
  void setClockFactor(float _factor);
};

#endif