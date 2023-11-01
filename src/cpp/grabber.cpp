#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include "grabber.hpp"
#include <iostream>

Grabber::Grabber() {
  column = 0;

  state = GrabberState::STARTING;

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

void Grabber::openGripper() {
  grabLeft.setOrigin(sf::Vector2f(27, 14));
  grabRight.setOrigin(sf::Vector2f(-11, 14));
  grabHori.setScale((GameConstants::CRATE_SIZE.x + 6 * grabHori.getScale().x) /
                        grabVert.getLocalBounds().width,
                    (GameConstants::CRATE_SIZE.y) /
                        grabVert.getLocalBounds().height);
}

void Grabber::closeGripper() {
  grabLeft.setOrigin(sf::Vector2f(24, 14));
  grabRight.setOrigin(sf::Vector2f(-8, 14));
  grabHori.setScale(
      (GameConstants::CRATE_SIZE.x) / grabVert.getLocalBounds().width,
      (GameConstants::CRATE_SIZE.y) / grabVert.getLocalBounds().height);
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

void Grabber::update() {
  switch (state) {
  case GrabberState::STARTING:
    setPosition(GameConstants::GRABBER_START_POS);
    state = GrabberState::FULL;
    break;
  case GrabberState::EMPTY:
    openGripper();
    break;
  case GrabberState::FULL:
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
}