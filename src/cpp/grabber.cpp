#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include "grabber.hpp"
#include <iostream>

Grabber::Grabber() {
  column = 3.5;

  state = GrabberState::STARTING;
  nextState = GrabberState::STARTING;

  clock = sf::Clock();
  lastTime = clock.getElapsedTime();

  grabHori = sf::Sprite();
  grabHori.setTexture(GameConstants::Textures::GRABBER_HORI);
  grabHori.setScale(
      GameConstants::CRATE_SIZE.x / grabHori.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / grabHori.getLocalBounds().height);
  grabHori.setOrigin(sf::Vector2f(8, 12));

  grabLeft = sf::Sprite();
  grabLeft.setTexture(GameConstants::Textures::GRABBER_LEFT);
  grabLeft.setScale(
      GameConstants::CRATE_SIZE.x / grabLeft.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / grabLeft.getLocalBounds().height);
  grabLeft.setOrigin(sf::Vector2f(24, 14));

  grabRight = sf::Sprite();
  grabRight.setTexture(GameConstants::Textures::GRABBER_RIGHT);
  grabRight.setScale(
      GameConstants::CRATE_SIZE.x / grabRight.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / grabRight.getLocalBounds().height);
  grabRight.setOrigin(sf::Vector2f(-8, 14));

  grabVert = sf::Sprite();
  grabVert.setTexture(GameConstants::Textures::GRABBER_VERT);
  grabVert.setScale(
      GameConstants::CRATE_SIZE.x / grabVert.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / grabVert.getLocalBounds().height);
  grabVert.setOrigin(sf::Vector2f(8, 0));

  // _centreDot.setFillColor(sf::Color(255, 0, 0));
  // _centreDot.setRadius(5);

  // _vertBoundingBox.setFillColor(sf::Color(0, 255, 0, 100));
  // _vertBoundingBox.setSize(sf::Vector2f(grabVert.getGlobalBounds().width,
  // grabVert.getGlobalBounds().height));
}

void Grabber::setPosition(sf::Vector2f pos) {
  grabHori.setPosition(pos);
  grabLeft.setPosition(pos);
  grabRight.setPosition(pos);
  grabVert.setPosition(sf::Vector2f(pos.x, GameConstants::BORDER_HEIGHT +
                                               GameConstants::BORDER_WIDTH));
  // grabVert.move(sf::Vector2f(0, -100));

  grabVert.setScale(GameConstants::CRATE_SIZE.x /
                        grabVert.getLocalBounds().width,
                    (pos.y - 98 - GameConstants::BORDER_HEIGHT) /
                        grabVert.getLocalBounds().height);
  // _vertBoundingBox.setOrigin(sf::Vector2f(_vertBoundingBox.getGlobalBounds().width
  // / 2, _vertBoundingBox.getGlobalBounds().height / 2));
  // _vertBoundingBox.setPosition(pos);

  // _centreDot.setPosition(grabVert.getPosition());
}

void Grabber::setPosition(int x, int y) { setPosition(sf::Vector2f(x, y)); }

void Grabber::move(sf::Vector2f delta) {
  grabHori.move(delta);
  grabLeft.move(delta);
  grabRight.move(delta);
  grabVert.move(sf::Vector2f(delta.x, 0));
  // grabVert.move(sf::Vector2f(0, -100));

  grabVert.setScale(
      GameConstants::CRATE_SIZE.x / grabVert.getLocalBounds().width,
      (grabHori.getPosition().y - 98 - GameConstants::BORDER_HEIGHT) /
          grabVert.getLocalBounds().height);
  // _vertBoundingBox.setOrigin(sf::Vector2f(_vertBoundingBox.getGlobalBounds().width
  // / 2, _vertBoundingBox.getGlobalBounds().height / 2));
  // _vertBoundingBox.setPosition(pos);

  // _centreDot.setPosition(grabVert.getPosition());
}

void Grabber::move(int x, int y) { move(sf::Vector2f(x, y)); }

void Grabber::openGripper() {
  grabLeft.setOrigin(sf::Vector2f(27, 14));
  grabRight.setOrigin(sf::Vector2f(-11, 14));
  grabHori.setScale((GameConstants::CRATE_SIZE.x + 6 * grabHori.getScale().x) /
                        grabVert.getLocalBounds().width,
                    (GameConstants::CRATE_SIZE.y) /
                        grabVert.getLocalBounds().height);
}

sf::Vector2f Grabber::getPosition() { return grabHori.getPosition(); }

void Grabber::closeGripper() {
  grabLeft.setOrigin(sf::Vector2f(24, 14));
  grabRight.setOrigin(sf::Vector2f(-8, 14));
  grabHori.setScale(
      (GameConstants::CRATE_SIZE.x) / grabVert.getLocalBounds().width,
      (GameConstants::CRATE_SIZE.y) / grabVert.getLocalBounds().height);
}

void Grabber::goTo(int _column, Crates &_crates) {
  switch (state) {
  case GrabberState::STARTING:
  case GrabberState::EMPTY:
    if (_crates.isLineGrabbable(_column))
      nextState = GrabberState::GRABBING;
    else
      nextState = GrabberState::EMPTY;
    if (column == _column)
      state = nextState;
    else if (_column < column) {
      state = GrabberState::SLIDINGLEFT;
    } else if (_column > column)
      state = GrabberState::SLIDINGRIGHT;
    column = _column;
    break;
  case GrabberState::FULL:
    if (_crates.linePlacable(_column))
      nextState = GrabberState::PLACING;
    else
      nextState = GrabberState::FULL;
    if (column == _column)
      state = nextState;
    else if (_column < column)
      state = GrabberState::SLIDINGLEFT;
    else if (_column > column)
      state = GrabberState::SLIDINGRIGHT;
    column = _column;
    break;
  default:
    break;
  }
}

void Grabber::drawGrabber(sf::RenderWindow &window) {
  window.draw(grabHori);
  window.draw(grabLeft);
  window.draw(grabRight);
  window.draw(grabVert);
  // window.draw(_vertBoundingBox);
  // window.draw(_centreDot);
  // std::cout
  //     << grabVert.getGlobalBounds().width << ", " <<
  //     grabVert.getGlobalBounds().height << std::endl;
}

void Grabber::update(Crates &_crates) {
  switch (state) {
  case GrabberState::STARTING:
    setPosition(GameConstants::GRABBER_START_POS);
    state = GrabberState::EMPTY;
    break;
  case GrabberState::EMPTY:
    break;
  case GrabberState::FULL:
    break;
  case GrabberState::SLIDINGLEFT:
    move(-(GameConstants::GRABBER_HORIZONTAL_SPEED *
           (clock.getElapsedTime().asMilliseconds() -
            lastTime.asMilliseconds())),
         0);
    if (getPosition().x < GameConstants::PLATFORM_POS[column].x) {
      setPosition(GameConstants::SPAWN_POS[column].x,
                  GameConstants::GRABBER_START_POS.y);
      state = nextState;
    }
    break;
  case GrabberState::SLIDINGRIGHT:
    move(
        (GameConstants::GRABBER_HORIZONTAL_SPEED *
         (clock.getElapsedTime().asMilliseconds() - lastTime.asMilliseconds())),
        0);
    if (getPosition().x > GameConstants::PLATFORM_POS[column].x) {
      setPosition(GameConstants::SPAWN_POS[column].x,
                  GameConstants::GRABBER_START_POS.y);
      state = nextState;
    }
    break;
  case GrabberState::GRABBING:
    break;
  case GrabberState::PLACING:
    break;
  case GrabberState::LIFTINGCRATE:
    break;
  case GrabberState::RETURNING:
    break;
  default:
    break;
  }
  lastTime = clock.getElapsedTime();
}

int Grabber::getColumn() { return std::abs(column); }
bool Grabber::isActive() {
  switch (state) {
  case GrabberState::GRABBING:
  case GrabberState::PLACING:
  case GrabberState::LIFTINGCRATE:
  case GrabberState::RETURNING:
    return true;
  default:
    return false;
  }
}